#ifndef __AE_H__
#define __AE_H__

#include <time.h>

#define AE_OK 0
#define AE_ERR -1

#define AE_NONE 0
#define AE_READABLE 1
#define AE_WRITABLE 2

#define AE_FILE_EVENTS 1
#define AE_TIME_EVENTS 2
#define AE_ALL_EVENTS (AE_FILE_EVENTS|AE_TIME_EVENTS)
#define AE_DONT_WAIT 4

#define AE_NOMORE -1

/* Macros */
#define AE_NOTUSED(V) ((void) V)

struct aeEventLoop;

/* Types and data structures */
typedef void aeFileProc(struct aeEventLoop *eventLoop, int fd, void *clientData, int mask);
typedef int aeTimeProc(struct aeEventLoop *eventLoop, long long id, void *clientData);
typedef void aeEventFinalizerProc(struct aeEventLoop *eventLoop, void *clientData);
typedef void aeBeforeSleepProc(struct aeEventLoop *eventLoop);

/* 已注册的socket事件,每一个socket fd对应一个该结构体*/
typedef struct aeFileEvent
{
    int mask; /* 要监听事件的类型 AE_(READABLE|WRITABLE) */
    aeFileProc *rfileProc; /* 读事件的响应函数 */
    aeFileProc *wfileProc; /* 写事件的响应函数 */
    void *clientData;
} aeFileEvent;

/* 定时器链表 */
typedef struct aeTimeEvent
{
    long long id; /* time event identifier. */
    long when_sec; /* seconds */
    long when_ms; /* milliseconds */
    aeTimeProc *timeProc; /* 定时器的响应函数 */
    aeEventFinalizerProc *finalizerProc; /* 删除定时器时的析构函数 */
    void *clientData;
    struct aeTimeEvent *next;
} aeTimeEvent;

/* 已触发的epoll事件 */
typedef struct aeFiredEvent
{
    int fd;//文件描述符
    int mask;//事件类型
} aeFiredEvent;

/* 基于epoll等机制实现的文件事件循环 */
typedef struct aeEventLoop
{
    int maxfd;   					/* 已注册的最大的事件描述符 */
    int setsize;				    /* max number of file descriptors tracked */
    long long timeEventNextId;     /* 指向下一个定时器 */
    time_t lastTime;    		    /* Used to detect system clock skew */
    aeFileEvent *events;		    /* 已注册的事件 */
    aeFiredEvent *fired;		    /* 已触发的epoll事件 */
    aeTimeEvent *timeEventHead;		/* 定时器事件的表头 */
    int stop;						//用于停止事件轮询
    void *apidata;				    /* 指向epoll的外包结构体aeApiState */
    aeBeforeSleepProc *beforesleep; /* 每次事件轮询前都会执行的函数，相当于hook*/
} aeEventLoop;

/* Prototypes */
aeEventLoop *aeCreateEventLoop(int setsize);
void aeDeleteEventLoop(aeEventLoop *eventLoop);
void aeStop(aeEventLoop *eventLoop);
int aeCreateFileEvent(aeEventLoop *eventLoop, int fd, int mask,
        aeFileProc *proc, void *clientData);
void aeDeleteFileEvent(aeEventLoop *eventLoop, int fd, int mask);
int aeGetFileEvents(aeEventLoop *eventLoop, int fd);
long long aeCreateTimeEvent(aeEventLoop *eventLoop, long long milliseconds,
        aeTimeProc *proc, void *clientData,
        aeEventFinalizerProc *finalizerProc);
int aeDeleteTimeEvent(aeEventLoop *eventLoop, long long id);
int aeProcessEvents(aeEventLoop *eventLoop, int flags);
int aeWait(int fd, int mask, long long milliseconds);
void aeMain(aeEventLoop *eventLoop);
char *aeGetApiName(void);
void aeSetBeforeSleepProc(aeEventLoop *eventLoop, aeBeforeSleepProc *beforesleep);
int aeGetSetSize(aeEventLoop *eventLoop);
int aeResizeSetSize(aeEventLoop *eventLoop, int setsize);

#endif
