/*
#include <pthread.h>

// 获取线程栈尺寸
int pthread_attr_getstacksize(const pthread_attr_t *restrict attr,
                              size_t *restrict stacksize);
    // parameter:
        - attr: 传入参数，需要获取栈尺寸的线程属性联合体
        - stacksize: 传出参数，栈尺寸（字节）
    
    // return:
        - 成功返回 0，失败返回错误码
 */

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <pthread.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

#define handleError(no, msg)        \
        do {                        \
            errno = no;             \
            perror(msg);            \
            exit(EXIT_FAILURE);     \
        } while (0)

void *foo(void *arg) {
    int ret = 0;

    // 获取线程属性联合体
    pthread_attr_t pattr;
    ret = pthread_getattr_np(pthread_self(), &pattr);
    if (ret != 0) {
        handleError(ret, "pthread_getattr_np");
    }

    // 获取线程栈尺寸
    size_t stack_size;
    ret = pthread_attr_getstacksize(&pattr, &stack_size);
    if (ret != 0) {
        handleError(ret, "pthread_attr_getstacksize");
    }
    printf("thread stack size: %lu\n", stack_size);

    // 设置线程栈尺寸
    ret = pthread_attr_setstacksize(&pattr, 10485760);
    if (ret != 0) {
        handleError(ret, "pthread_attr_setstacksize");
    }

    ret = pthread_attr_getstacksize(&pattr, &stack_size);
    printf("thread stack size: %lu\n", stack_size);

    // 销毁线程属性联合体
    pthread_attr_destroy(&pattr);
    return NULL;
}

int main() {
    pthread_t pid;
    pthread_create(&pid, NULL, foo, NULL);
    pthread_join(pid, NULL);
    printf("%ld\n", PTHREAD_STACK_MIN);
    return 0;
}