#ifndef __ADLIST_H__
#define __ADLIST_H__

/* 双向链表的结点 */
typedef struct listNode {
    struct listNode *prev;
    struct listNode *next;
    void *value;
} listNode;

/* 链表访问迭代器 */
typedef struct listIter {
    listNode *next;//指向链表的某个结点
    int direction;//表示迭代器的方向，AL_START_HEAD向前，AL_START_TAIL向后
} listIter;

typedef struct list
{
    listNode *head;
    listNode *tail;
    void *(*dup)(void *ptr);//复制链表中结点的值
    void (*free)(void *ptr);//释放链表中结点的值
    int (*match)(void *ptr, void *key);//匹配链表中结点的值
    unsigned long len;//链表的长度
} list;

/* Functions implemented as macros */
#define listLength(l) ((l)->len)
#define listFirst(l) ((l)->head)
#define listLast(l) ((l)->tail)
#define listPrevNode(n) ((n)->prev)
#define listNextNode(n) ((n)->next)
#define listNodeValue(n) ((n)->value)

#define listSetDupMethod(l,m) ((l)->dup = (m))
#define listSetFreeMethod(l,m) ((l)->free = (m))
#define listSetMatchMethod(l,m) ((l)->match = (m))

#define listGetDupMethod(l) ((l)->dup)
#define listGetFree(l) ((l)->free)
#define listGetMatchMethod(l) ((l)->match)

/* Prototypes */
list *listCreate(void);
void listRelease(list *list);
list *listAddNodeHead(list *list, void *value);
list *listAddNodeTail(list *list, void *value);
list *listInsertNode(list *list, listNode *old_node, void *value, int after);
void listDelNode(list *list, listNode *node);
listIter *listGetIterator(list *list, int direction);
listNode *listNext(listIter *iter);
void listReleaseIterator(listIter *iter);
list *listDup(list *orig);
listNode *listSearchKey(list *list, void *key);
listNode *listIndex(list *list, long index);
void listRewind(list *list, listIter *li);
void listRewindTail(list *list, listIter *li);
void listRotate(list *list);

/* Directions for iterators */
#define AL_START_HEAD 0
#define AL_START_TAIL 1

#endif /* __ADLIST_H__ */
