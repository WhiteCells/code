/*
#include <pthread.h>

// 设置线程分离状态为可分离
int pthread_detach(pthread_t thread);
    // parameter:
        - thread: 设置为可分离的线程的线程 ID

    // return:
        - 成功返回 0，失败返回 errno
 */

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#define handleError(no, msg)    \
        do {                    \
            errno = no;         \
            perror(msg);        \
            exit(EXIT_FAILURE); \
        } while (0)

void printPThreadDetachstate(const char *name, pthread_t pid) {
    int ret = 0;

    // 获取线程属性联合体
    pthread_attr_t pattr;
    ret = pthread_getattr_np(pid, &pattr);
    if (ret != 0) {
        handleError(ret, "pthread_getattr_np");
    }

    // 从线程属性联合体中获取分离状态属性
    int detachstate = 0;
    ret = pthread_attr_getdetachstate(&pattr, &detachstate);
    if (ret != 0) {
        handleError(ret, "pthread_attr_getdetachstate");
    }

    switch (detachstate) {
        case PTHREAD_CREATE_DETACHED:
            printf("%s thread is detached thread\n", name);
            break;
        case PTHREAD_CREATE_JOINABLE:
            printf("%s thread is joinable thread\n", name);
            break;
        default:
            break;
    }

    // 销毁线程属性联合体
    pthread_attr_destroy(&pattr);
}

/* sub1 线程函数 */
void *foo(void *arg) {
    const char *thread_name = (const char *)arg;
    // 子线程打印线程分离状态
    printPThreadDetachstate(thread_name, pthread_self());
    return NULL;
}

/* sub2 线程函数 */
void *foo2(void *arg) {
    const char *thread_name = (const char *)arg;
    // 设置分离状态为可分离的
    int ret = pthread_detach(pthread_self());
    if (ret != 0) {
        handleError(ret, "pthread_detach");
    }
    printPThreadDetachstate(thread_name, pthread_self());
    return NULL;
}

int main(int argc, char *argv[]) {
    // 主线程打印线程分离状态
    printPThreadDetachstate("main", pthread_self());

    int ret = 0;

    // 创建默认线程属性联合体
    pthread_attr_t pattr;
    ret = pthread_attr_init(&pattr);
    if (ret != 0) {
        handleError(ret, "pthread_attr_init");
    }

    // 线程属性联合体设置分离状态
    ret = pthread_attr_setdetachstate(&pattr, PTHREAD_CREATE_DETACHED);
    if (ret != 0) {
        handleError(ret, "pthread_attr_setdetachstate");
    }

    // 使用上述线程属性联合体创建线程
    pthread_t pid;
    char thread_name[] = {"sub1"};
    ret = pthread_create(&pid, &pattr, foo, thread_name);
    if (ret != 0) {
        handleError(ret, "pthread_create");
    }

    // 创建默认可连接线程
    pthread_t pid2;
    char thread_name2[] = {"sub2"};
    ret = pthread_create(&pid2, NULL, foo2, thread_name2);

    // 主线程退出
    pthread_exit(NULL);
}