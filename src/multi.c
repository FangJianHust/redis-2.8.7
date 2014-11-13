#include "redis.h"

/* ================================ MULTI/EXEC ============================== */

/* Client state initialization for MULTI/EXEC */
void initClientMultiState(redisClient *c) {
    c->mstate.commands = NULL;
    c->mstate.count = 0;
}

/* Release all the resources associated with MULTI/EXEC state */
void freeClientMultiState(redisClient *c) {
    int j;
    for (j = 0; j < c->mstate.count; j++)
    {
        int i;
        multiCmd *mc = c->mstate.commands+j;
        for (i = 0; i < mc->argc; i++)
            decrRefCount(mc->argv[i]);
        zfree(mc->argv);
    }
    zfree(c->mstate.commands);
}

/* Add a new command into the MULTI commands queue */
void queueMultiCommand(redisClient *c)
{
    multiCmd *mc;
    int j;
    c->mstate.commands = zrealloc(c->mstate.commands, sizeof(multiCmd)*(c->mstate.count+1)); // 重分配空间，为新命令申请空间
    // 指针指向新分配的空间，并将命令内容保存进去
    mc = c->mstate.commands+c->mstate.count;
    mc->cmd = c->cmd;	// 保存要执行的命令
    mc->argc = c->argc; // 保存命令参数的数量
    mc->argv = zmalloc(sizeof(robj*)*c->argc);
    memcpy(mc->argv,c->argv,sizeof(robj*)*c->argc);
    for (j = 0; j < c->argc; j++)
        incrRefCount(mc->argv[j]);
    c->mstate.count++;
}

void discardTransaction(redisClient *c) {
    freeClientMultiState(c);
    initClientMultiState(c);
    c->flags &= ~(REDIS_MULTI|REDIS_DIRTY_CAS|REDIS_DIRTY_EXEC);;
    unwatchAllKeys(c);
}

/* Flag the transacation as DIRTY_EXEC so that EXEC will fail.
 * Should be called every time there is an error while queueing a command. */
void flagTransaction(redisClient *c) {
    if (c->flags & REDIS_MULTI)
        c->flags |= REDIS_DIRTY_EXEC;
}

/* multi命令 */
void multiCommand(redisClient *c) {
    if (c->flags & REDIS_MULTI)
    {
        addReplyError(c,"MULTI calls can not be nested");
        return;
    }
    /* 打开事务的FLAG从此之后，除 DISCARD 和 EXEC 等少数几个命令之外其他所有的命令都会被添加到事务队列里  */
    c->flags |= REDIS_MULTI;
    addReply(c,shared.ok);
}

void discardCommand(redisClient *c) {
    if (!(c->flags & REDIS_MULTI)) {
        addReplyError(c,"DISCARD without MULTI");
        return;
    }
    discardTransaction(c);
    addReply(c,shared.ok);
}

/* Send a MULTI command to all the slaves and AOF file. Check the execCommand
 * implementation for more information. */
void execCommandPropagateMulti(redisClient *c) {
    robj *multistring = createStringObject("MULTI",5);

    propagate(server.multiCommand,c->db->id,&multistring,1,
              REDIS_PROPAGATE_AOF|REDIS_PROPAGATE_REPL);
    decrRefCount(multistring);
}

/* exec命令 */
void execCommand(redisClient *c)
{
    int j;
    robj **orig_argv;
    int orig_argc;
    struct redisCommand *orig_cmd;
    int must_propagate = 0; /* Need to propagate MULTI/EXEC to AOF / slaves? */
    if (!(c->flags & REDIS_MULTI))
    {
        addReplyError(c,"EXEC without MULTI");
        return;
    }
    /* Check if we need to abort the EXEC because:
     * 1) Some WATCHed key was touched.此时REDIS_DIRTY_CAS被设置
     * 2) There was a previous error while queueing commands(如事务中的命令格式不正确).此时REDIS_DIRTY_EXEC被设置
     * A failed EXEC in the first case returns a multi bulk nil object(technically it is not an error but a special
     * behavior), while in the second an EXECABORT error is returned. */
    if (c->flags & (REDIS_DIRTY_CAS|REDIS_DIRTY_EXEC))
    {
        addReply(c, c->flags & REDIS_DIRTY_EXEC ? shared.execaborterr : shared.nullmultibulk);
        discardTransaction(c);
        goto handle_monitor;
    }
    unwatchAllKeys(c); /* Unwatch ASAP otherwise we'll waste CPU cycles */
    orig_argv = c->argv;
    orig_argc = c->argc;
    orig_cmd = c->cmd;
    addReplyMultiBulkLen(c,c->mstate.count);
    //取出每一条命令执行
    for (j = 0; j < c->mstate.count; j++)
    {
        c->argc = c->mstate.commands[j].argc;
        c->argv = c->mstate.commands[j].argv;
        c->cmd = c->mstate.commands[j].cmd;
        /* Propagate a MULTI request once we encounter the first write op. This way we'll deliver the MULTI/..../EXEC  block
         * as a whole and both the AOF and the replication link will have the same consistency and atomicity  guarantees. */
        if (!must_propagate && !(c->cmd->flags & REDIS_CMD_READONLY))
        {
            execCommandPropagateMulti(c);
            must_propagate = 1;
        }
        call(c,REDIS_CALL_FULL);
        /* Commands may alter argc/argv, restore mstate. */
        c->mstate.commands[j].argc = c->argc;
        c->mstate.commands[j].argv = c->argv;
        c->mstate.commands[j].cmd = c->cmd;
    }
    c->argv = orig_argv;
    c->argc = orig_argc;
    c->cmd = orig_cmd;
    discardTransaction(c);
    /* Make sure the EXEC command will be propagated as well if MULTI was already propagated. */
    if (must_propagate) server.dirty++;
handle_monitor:
    /* Send EXEC to clients waiting data from MONITOR. We do it here since the natural order of commands execution is
     * actually: MUTLI, EXEC, ... commands inside transaction ...
     * Instead EXEC is flagged as REDIS_CMD_SKIP_MONITOR in the command table, and we do it here with correct ordering. */
    if (listLength(server.monitors) && !server.loading)
        replicationFeedMonitors(c,server.monitors,c->db->id,c->argv,c->argc);
}

/* ===================== WATCH (CAS alike for MULTI/EXEC) ===================
 *
 * The implementation uses a per-DB hash table mapping keys to list of clients WATCHing those keys, so that given a key
 * that is going to be modified we can mark all the associated clients as dirty.
 *
 * Also every client contains a list of WATCHed keys so that's possible to un-watch such keys when the client is freed
 * or when UNWATCH is called. */

/* In the client->watched_keys list we need to use watchedKey structures as in order to identify a key in Redis we need
 * both the key name and the DB */
typedef struct watchedKey
{
    robj *key;  //要监视的key
    redisDb *db;//该key所属的redisDb
} watchedKey;

/* watch命令在multi提交之前执行，watchCommand()执行watchForKey()来监视key。Redis中实现监视key的方式很简单，每个Redis DB都会存储一个
 * 叫做watched_keys的key为被监视key，value为客户端队列的dict结构。而客户端也有watched_keys列表结构成员，该列表的元素是watchedKey结构。
 * 存储了该客户端监视的keys。这样，watchForKey()只要先去客户端的watched_keys查看是否已经监视这个key，若没有再去DB的watched_keys dict
 * 成员中加入这个监视key，最后在自己的watched_keys中加入新的监视key。 unwatchAllKeys()会删除该客户端监视的所有keys，然后到对应的DB的
 * watched_keys中删掉该客户端。 参考http://www.chepoo.com/redis-analysis-transaction-multi-cas.html*/
void watchForKey(redisClient *c, robj *key)
{
    list *clients = NULL;
    listIter li;
    listNode *ln;
    watchedKey *wk;
    /* Check if we are already watching for this key */
    listRewind(c->watched_keys,&li);
    while((ln = listNext(&li)))
    {
        wk = listNodeValue(ln);
        if (wk->db == c->db && equalStringObjects(key,wk->key))
            return; /* Key already watched */
    }
    /* This key is not already watched in this DB. Let's add it */
    clients = dictFetchValue(c->db->watched_keys,key);
    if (!clients)
    {
        clients = listCreate();
        dictAdd(c->db->watched_keys,key,clients);
        incrRefCount(key);
    }
    listAddNodeTail(clients,c);
    /* Add the new key to the list of keys watched by this client */
    wk = zmalloc(sizeof(*wk));
    wk->key = key;
    wk->db = c->db;
    incrRefCount(key);
    listAddNodeTail(c->watched_keys,wk);
}

/* Unwatch all the keys watched by this client. To clean the EXEC dirty flag is up to the caller. */
void unwatchAllKeys(redisClient *c)
{
    listIter li;
    listNode *ln;
    if (listLength(c->watched_keys) == 0) return;
    listRewind(c->watched_keys,&li);
    while((ln = listNext(&li)))
    {
        list *clients;
        watchedKey *wk;
        /* Lookup the watched key -> clients list and remove the client from the list */
        wk = listNodeValue(ln);
        clients = dictFetchValue(wk->db->watched_keys, wk->key);
        redisAssertWithInfo(c,NULL,clients != NULL);
        listDelNode(clients,listSearchKey(clients,c));
        /* Kill the entry at all if this was the only client */
        if (listLength(clients) == 0)
            dictDelete(wk->db->watched_keys, wk->key);
        /* Remove this watched key from the client->watched list */
        listDelNode(c->watched_keys,ln);
        decrRefCount(wk->key);
        zfree(wk);
    }
}

/* "Touch" a key, so that if this key is being WATCHed by some client the
 * next EXEC will fail. */
void touchWatchedKey(redisDb *db, robj *key) {
    list *clients;
    listIter li;
    listNode *ln;

    if (dictSize(db->watched_keys) == 0) return;
    clients = dictFetchValue(db->watched_keys, key);
    if (!clients) return;

    /* Mark all the clients watching this key as REDIS_DIRTY_CAS */
    /* Check if we are already watching for this key */
    listRewind(clients,&li);
    while((ln = listNext(&li))) {
        redisClient *c = listNodeValue(ln);

        c->flags |= REDIS_DIRTY_CAS;
    }
}

/* On FLUSHDB or FLUSHALL all the watched keys that are present before the
 * flush but will be deleted as effect of the flushing operation should
 * be touched. "dbid" is the DB that's getting the flush. -1 if it is
 * a FLUSHALL operation (all the DBs flushed). */
void touchWatchedKeysOnFlush(int dbid) {
    listIter li1, li2;
    listNode *ln;

    /* For every client, check all the waited keys */
    listRewind(server.clients,&li1);
    while((ln = listNext(&li1))) {
        redisClient *c = listNodeValue(ln);
        listRewind(c->watched_keys,&li2);
        while((ln = listNext(&li2))) {
            watchedKey *wk = listNodeValue(ln);

            /* For every watched key matching the specified DB, if the
             * key exists, mark the client as dirty, as the key will be
             * removed. */
            if (dbid == -1 || wk->db->id == dbid) {
                if (dictFind(wk->db->dict, wk->key->ptr) != NULL)
                    c->flags |= REDIS_DIRTY_CAS;
            }
        }
    }
}

void watchCommand(redisClient *c)
{
    int j;
    if (c->flags & REDIS_MULTI)
    {
        addReplyError(c,"WATCH inside MULTI is not allowed");
        return;
    }
    for (j = 1; j < c->argc; j++)
        watchForKey(c,c->argv[j]);
    addReply(c,shared.ok);
}

void unwatchCommand(redisClient *c) {
    unwatchAllKeys(c);
    c->flags &= (~REDIS_DIRTY_CAS);
    addReply(c,shared.ok);
}
