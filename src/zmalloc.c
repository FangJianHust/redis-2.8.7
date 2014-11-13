#include <stdio.h>
#include <stdlib.h>

/* This function provide us access to the original libc free(). This is useful
 * for instance to free results obtained by backtrace_symbols(). We need
 * to define this function before including zmalloc.h that may shadow the
 * free implementation if we use jemalloc or another non standard allocator. */
void zlibc_free(void *ptr) {
    free(ptr);
}

#include <string.h>
#include <pthread.h>
#include "config.h"
#include "zmalloc.h"

#ifdef HAVE_MALLOC_SIZE
#define PREFIX_SIZE (0)
#else
#if defined(__sun) || defined(__sparc) || defined(__sparc__)
#define PREFIX_SIZE (sizeof(long long))
#else
#define PREFIX_SIZE (sizeof(unsigned int))
#endif
#endif

/* Explicitly override malloc/free etc when using tcmalloc. */
#if defined(USE_TCMALLOC)
#define malloc(size) tc_malloc(size)
#define calloc(count,size) tc_calloc(count,size)
#define realloc(ptr,size) tc_realloc(ptr,size)
#define free(ptr) tc_free(ptr)
#elif defined(USE_JEMALLOC)
#define malloc(size) je_malloc(size)
#define calloc(count,size) je_calloc(count,size)
#define realloc(ptr,size) je_realloc(ptr,size)
#define free(ptr) je_free(ptr)
#endif

#ifdef HAVE_ATOMIC
#define update_zmalloc_stat_add(__n) __sync_add_and_fetch(&used_memory, (__n))
#define update_zmalloc_stat_sub(__n) __sync_sub_and_fetch(&used_memory, (__n))
#else
#define update_zmalloc_stat_add(__n) do { \
    pthread_mutex_lock(&used_memory_mutex); \
    used_memory += (__n); \
    pthread_mutex_unlock(&used_memory_mutex); \
} while(0)

#define update_zmalloc_stat_sub(__n) do { \
    pthread_mutex_lock(&used_memory_mutex); \
    used_memory -= (__n); \
    pthread_mutex_unlock(&used_memory_mutex); \
} while(0)

#endif

static int zmalloc_thread_safe = 0;
static unsigned int used_memory = 0;//记录了使用的内存总数
/* 记录申请的内存块的相关信息，以便监控内存使用的状况 */
void update_zmalloc_stat_alloc(__n)
{
	unsigned int _n = (__n);
	if (_n&(sizeof(long)-1)) _n += sizeof(long)-(_n&(sizeof(long)-1));
	if (zmalloc_thread_safe) {
		//update_zmalloc_stat_add(_n);
	}
	else
	{
		used_memory += _n;
	}
}
/*#define update_zmalloc_stat_alloc(__n) do { \
    unsigned int _n = (__n); \
    if (_n&(sizeof(long)-1)) _n += sizeof(long)-(_n&(sizeof(long)-1)); \ //将要分配的空间与内存对齐
if (zmalloc_thread_safe) { \	//如果是多线程，则需要进行加锁
      update_zmalloc_stat_add(_n); \
  } else { \
      used_memory += _n; \
  } \
} while(0)*/

/**
 * 进行内存释放
 */
#define update_zmalloc_stat_free(__n) do { \
    unsigned int _n = (__n); \
    if (_n&(sizeof(long)-1)) _n += sizeof(long)-(_n&(sizeof(long)-1)); \
    if (zmalloc_thread_safe) { \
        update_zmalloc_stat_sub(_n); \
    } else { \
        used_memory -= _n; \
    } \
} while(0)




pthread_mutex_t used_memory_mutex = PTHREAD_MUTEX_INITIALIZER;

static void zmalloc_default_oom(unsigned int size)
{
    fprintf(stderr, "zmalloc: Out of memory trying to allocate %zu bytes\n",size);
    fflush(stderr);
    abort();
}

static void (*zmalloc_oom_handler)(unsigned int) = zmalloc_default_oom;//new_handler函数指针

void *zmalloc(unsigned int size)
{
	//多申请一块定长的区域用于记录所申请的内存块的长度
    void *ptr = malloc(size+PREFIX_SIZE);

    if (!ptr) zmalloc_oom_handler(size);//模拟c++的new handler机制
#ifdef HAVE_MALLOC_SIZE
    update_zmalloc_stat_alloc(zmalloc_size(ptr));
    return ptr;
#else
    *((unsigned int*)ptr) = size;//在内存块头部保存了内存块的大小
    update_zmalloc_stat_alloc(size+PREFIX_SIZE);
    return (char*)ptr+PREFIX_SIZE;
#endif
}

void *zcalloc(unsigned int size)
{
    void *ptr = calloc(1, size+PREFIX_SIZE);
    if (!ptr) zmalloc_oom_handler(size);
#ifdef HAVE_MALLOC_SIZE
    update_zmalloc_stat_alloc(zmalloc_size(ptr));
    return ptr;
#else
    *((unsigned int*)ptr) = size;//在内存块头部保存了内存块的大小
    update_zmalloc_stat_alloc(size+PREFIX_SIZE);
    return (char*)ptr+PREFIX_SIZE;
#endif
}

void *zrealloc(void *ptr, unsigned int size) {
#ifndef HAVE_MALLOC_SIZE
    void *realptr;
#endif
    unsigned int oldsize;
    void *newptr;

    if (ptr == NULL) return zmalloc(size);
#ifdef HAVE_MALLOC_SIZE
    oldsize = zmalloc_size(ptr);
    newptr = realloc(ptr,size);
    if (!newptr) zmalloc_oom_handler(size);

    update_zmalloc_stat_free(oldsize);
    update_zmalloc_stat_alloc(zmalloc_size(newptr));
    return newptr;
#else
    realptr = (char*)ptr-PREFIX_SIZE;
    oldsize = *((unsigned int*)realptr);
    newptr = realloc(realptr,size+PREFIX_SIZE);
    if (!newptr) zmalloc_oom_handler(size);

    *((unsigned int*)newptr) = size;
    update_zmalloc_stat_free(oldsize);
    update_zmalloc_stat_alloc(size);
    return (char*)newptr+PREFIX_SIZE;
#endif
}

/* Provide zmalloc_size() for systems where this function is not provided by
 * malloc itself, given that in that case we store a header with this
 * information as the first bytes of every allocation. */
#ifndef HAVE_MALLOC_SIZE
unsigned int zmalloc_size(void *ptr) {
    void *realptr = (char*)ptr-PREFIX_SIZE;
    unsigned int size = *((unsigned int*)realptr);
    /* Assume at least that all the allocations are padded at sizeof(long) by
     * the underlying allocator. */
    if (size&(sizeof(long)-1)) size += sizeof(long)-(size&(sizeof(long)-1));
    return size+PREFIX_SIZE;
}
#endif

void zfree(void *ptr) {
#ifndef HAVE_MALLOC_SIZE
    void *realptr;
    unsigned int oldsize;
#endif

    if (ptr == NULL) return;
#ifdef HAVE_MALLOC_SIZE //Mac OS 支持
    update_zmalloc_stat_free(zmalloc_size(ptr));
    free(ptr);
#else
    /* 根据头部信息获取被释放内存区域的长度 */
    realptr = (char*)ptr-PREFIX_SIZE;
    oldsize = *((unsigned int*)realptr);
    update_zmalloc_stat_free(oldsize+PREFIX_SIZE);
    free(realptr);
#endif
}

/**
 * 申请一个新的空间，将字符串s复制到该空间后返回
 */
char *zstrdup(const char *s) {
    unsigned int l = strlen(s)+1;
    char *p = zmalloc(l);

    memcpy(p,s,l);
    return p;
}

unsigned int zmalloc_used_memory(void) {
    unsigned int um;

    if (zmalloc_thread_safe) {
#ifdef HAVE_ATOMIC
        um = __sync_add_and_fetch(&used_memory, 0);
#else
        pthread_mutex_lock(&used_memory_mutex);
        um = used_memory;
        pthread_mutex_unlock(&used_memory_mutex);
#endif
    }
    else {
        um = used_memory;
    }

    return um;
}

/* 开启线程安全标志 */
void zmalloc_enable_thread_safeness(void)
{
    zmalloc_thread_safe = 1;
}

/* 设置内存溢出处理的函数，相当于c++的new handler机制 */
void zmalloc_set_oom_handler(void (*oom_handler)(unsigned int))
{
    zmalloc_oom_handler = oom_handler;
}

/* Get the RSS information in an OS-specific way.
 *
 * WARNING: the function zmalloc_get_rss() is not designed to be fast
 * and may not be called in the busy loops where Redis tries to release
 * memory expiring or swapping out objects.
 *
 * For this kind of "fast RSS reporting" usages use instead the
 * function RedisEstimateRSS() that is a much faster (and less precise)
 * version of the function. */

#if defined(HAVE_PROC_STAT)
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

unsigned int zmalloc_get_rss(void) {
    int page = sysconf(_SC_PAGESIZE);
    unsigned int rss;
    char buf[4096];
    char filename[256];
    int fd, count;
    char *p, *x;

    snprintf(filename,256,"/proc/%d/stat",getpid());
    if ((fd = open(filename,O_RDONLY)) == -1) return 0;
    if (read(fd,buf,4096) <= 0) {
        close(fd);
        return 0;
    }
    close(fd);

    p = buf;
    count = 23; /* RSS is the 24th field in /proc/<pid>/stat */
    while(p && count--) {
        p = strchr(p,' ');
        if (p) p++;
    }
    if (!p) return 0;
    x = strchr(p,' ');
    if (!x) return 0;
    *x = '\0';

    rss = strtoll(p,NULL,10);
    rss *= page;
    return rss;
}
#elif defined(HAVE_TASKINFO)
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/sysctl.h>
#include <mach/task.h>
#include <mach/mach_init.h>

unsigned int zmalloc_get_rss(void) {
    task_t task = MACH_PORT_NULL;
    struct task_basic_info t_info;
    mach_msg_type_number_t t_info_count = TASK_BASIC_INFO_COUNT;

    if (task_for_pid(current_task(), getpid(), &task) != KERN_SUCCESS)
        return 0;
    task_info(task, TASK_BASIC_INFO, (task_info_t)&t_info, &t_info_count);

    return t_info.resident_size;
}
#else
unsigned int zmalloc_get_rss(void) {
    /* If we can't get the RSS in an OS-specific way for this system just
     * return the memory usage we estimated in zmalloc()..
     *
     * Fragmentation will appear to be always 1 (no fragmentation)
     * of course... */
    return zmalloc_used_memory();
}
#endif

/* Fragmentation = RSS / allocated-bytes */
float zmalloc_get_fragmentation_ratio(void) {
    return (float)zmalloc_get_rss()/zmalloc_used_memory();
}

#if defined(HAVE_PROC_SMAPS)
unsigned int zmalloc_get_private_dirty(void) {
    char line[1024];
    unsigned int pd = 0;
    FILE *fp = fopen("/proc/self/smaps","r");

    if (!fp) return 0;
    while(fgets(line,sizeof(line),fp) != NULL) {
        if (strncmp(line,"Private_Dirty:",14) == 0) {
            char *p = strchr(line,'k');
            if (p) {
                *p = '\0';
                pd += strtol(line+14,NULL,10) * 1024;
            }
        }
    }
    fclose(fp);
    return pd;
}
#else
unsigned int zmalloc_get_private_dirty(void) {
    return 0;
}
#endif
