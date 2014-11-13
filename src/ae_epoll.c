#include <sys/epoll.h>
#include "ae.h"
/**
 * epoll的外包结构体
 */
typedef struct aeApiState
{
    int epfd;//epoll_create返回的epoll描述符
    struct epoll_event *events;//用于存放epoll_wait返回的已触发的事件数组
} aeApiState;

/* 申请并初始化epoll的包装结构体aeApiState */
static int aeApiCreate(aeEventLoop *eventLoop)
{
    aeApiState *state = zmalloc(sizeof(aeApiState));
    if (!state) return -1;
    //申请eventLoop->setsize个epoll_event结构体
    state->events = zmalloc(sizeof(struct epoll_event)*eventLoop->setsize);
    if (!state->events)
    {
        zfree(state);
        return -1;
    }
    state->epfd = epoll_create(1024); /* 1024 is just a hint for the kernel */
    if (state->epfd == -1)
    {
        zfree(state->events);
        zfree(state);
        return -1;
    }
    eventLoop->apidata = state;
    return 0;
}

static int aeApiResize(aeEventLoop *eventLoop, int setsize)
{
    aeApiState *state = eventLoop->apidata;
    state->events = zrealloc(state->events, sizeof(struct epoll_event)*setsize);
    return 0;
}

/**
 * 释放epoll结构体
 */
static void aeApiFree(aeEventLoop *eventLoop) {
    aeApiState *state = eventLoop->apidata;

    close(state->epfd);
    zfree(state->events);
    zfree(state);
}

/**
 * 调用epoll_ctl把事件添加到epoll中
 */
static int aeApiAddEvent(aeEventLoop *eventLoop, int fd, int mask)
{
    aeApiState *state = eventLoop->apidata;
    struct epoll_event ee;
    /* If the fd was already monitored for some event, we need a MOD operation. Otherwise we need an ADD operation. */
    int op = eventLoop->events[fd].mask == AE_NONE ? EPOLL_CTL_ADD : EPOLL_CTL_MOD;
    ee.events = 0;
    mask |= eventLoop->events[fd].mask; /* Merge old events */
    if (mask & AE_READABLE) ee.events |= EPOLLIN;
    if (mask & AE_WRITABLE) ee.events |= EPOLLOUT;
    ee.data.u64 = 0; /* avoid valgrind warning */
    ee.data.fd = fd;
    if (epoll_ctl(state->epfd,op,fd,&ee) == -1) return -1;
    return 0;
}

/* 删除fd上的delmask事件 */
static void aeApiDelEvent(aeEventLoop *eventLoop, int fd, int delmask)
{
    aeApiState *state = eventLoop->apidata;
    struct epoll_event ee;
    int mask = eventLoop->events[fd].mask & (~delmask);
    ee.events = 0;
    if (mask & AE_READABLE) ee.events |= EPOLLIN;
    if (mask & AE_WRITABLE) ee.events |= EPOLLOUT;
    ee.data.u64 = 0; /* avoid valgrind warning */
    ee.data.fd = fd;
    if (mask != AE_NONE)
    {
        epoll_ctl(state->epfd,EPOLL_CTL_MOD,fd,&ee);
    }
    else
    {
        /* Note, Kernel < 2.6.9 requires a non null event pointer even for EPOLL_CTL_DEL. */
        epoll_ctl(state->epfd,EPOLL_CTL_DEL,fd,&ee);
    }
}

/* 调用epoll_wait等待事件触发 */
static int aeApiPoll(aeEventLoop *eventLoop, struct timeval *tvp)
{
    aeApiState *state = eventLoop->apidata;
    int retval, numevents = 0;
    retval = epoll_wait(state->epfd,state->events,eventLoop->setsize,tvp ? (tvp->tv_sec*1000 + tvp->tv_usec/1000) : -1);
    if (retval > 0)
    {
        int j;
        numevents = retval;
        //把每一个已触发的epoll事件添加到eventLoop->fired数组中
        for (j = 0; j < numevents; j++)
        {
            int mask = 0;
            struct epoll_event *e = state->events+j;
            if (e->events & EPOLLIN) mask |= AE_READABLE;
            if (e->events & EPOLLOUT) mask |= AE_WRITABLE;
            if (e->events & EPOLLERR) mask |= AE_WRITABLE;
            if (e->events & EPOLLHUP) mask |= AE_WRITABLE;
            eventLoop->fired[j].fd = e->data.fd;
            eventLoop->fired[j].mask = mask;
        }
    }
    return numevents;
}

static char *aeApiName(void) {
    return "epoll";
}
