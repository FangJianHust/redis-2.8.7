#ifndef __SDS_H
#define __SDS_H

#define SDS_MAX_PREALLOC (1024*1024)

#include <sys/types.h>
#include <stdarg.h>

typedef char *sds;

/**
 * 封装的字符串结构
 */
struct sdshdr {
    int len;//字符串的长度
    int free;//可以额外使用的字节数
    char buf[];
};

/**
 * 获得sdshdr->len的值
 */
static inline unsigned int sdslen(const sds s) {
    struct sdshdr *sh = (void*)(s-(sizeof(struct sdshdr)));//通过sdshdr->buf指针获得sdshdr的地址
    return sh->len;
}

static inline unsigned int sdsavail(const sds s) {
    struct sdshdr *sh = (void*)(s-(sizeof(struct sdshdr)));
    return sh->free;
}

sds sdsnewlen(const void *init, unsigned int initlen);
sds sdsnew(const char *init);
sds sdsempty(void);
unsigned int sdslen(const sds s);
sds sdsdup(const sds s);
void sdsfree(sds s);
unsigned int sdsavail(const sds s);
sds sdsgrowzero(sds s, unsigned int len);
sds sdscatlen(sds s, const void *t, unsigned int len);
sds sdscat(sds s, const char *t);
sds sdscatsds(sds s, const sds t);
sds sdscpylen(sds s, const char *t, unsigned int len);
sds sdscpy(sds s, const char *t);

sds sdscatvprintf(sds s, const char *fmt, va_list ap);
#ifdef __GNUC__
sds sdscatprintf(sds s, const char *fmt, ...)
    __attribute__((format(printf, 2, 3)));
#else
sds sdscatprintf(sds s, const char *fmt, ...);
#endif

sds sdstrim(sds s, const char *cset);
void sdsrange(sds s, int start, int end);
void sdsupdatelen(sds s);
void sdsclear(sds s);
int sdscmp(const sds s1, const sds s2);
sds *sdssplitlen(const char *s, int len, const char *sep, int seplen, int *count);
void sdsfreesplitres(sds *tokens, int count);
void sdstolower(sds s);
void sdstoupper(sds s);
sds sdsfromlonglong(long long value);
sds sdscatrepr(sds s, const char *p, unsigned int len);
sds *sdssplitargs(const char *line, int *argc);
sds sdsmapchars(sds s, const char *from, const char *to, unsigned int setlen);
sds sdsjoin(char **argv, int argc, char *sep);

/* Low level functions exposed to the user API */
sds sdsMakeRoomFor(sds s, unsigned int addlen);
void sdsIncrLen(sds s, int incr);
sds sdsRemoveFreeSpace(sds s);
unsigned int sdsAllocSize(sds s);

#endif
