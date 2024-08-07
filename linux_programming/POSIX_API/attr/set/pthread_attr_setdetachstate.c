/*
#include <pthread.h>

// 设置线程属性联合体的分离状态属性
int pthread_attr_setdetachstate(pthread_attr_t *attr, int detachstate);
    // parameter:
        - attr: 需要设置的线程属性联合体变量
        - detachstate: 分离状态值

    // return:
        - 成功返回 0，失败返回错误码
    
    // note:
        - 分离状态宏：
            PTHREAD_CREATE_DETACHED
            PTHREAD_CREATE_JOINABLE
 */

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *foo(void *arg) {
    printf("sub thread\n");
    return NULL;
}

int main(int argc, char *argv[]) {
    int ret = 0;
    pthread_attr_t padttr;

    // 初始化线程属性联合体
    ret = pthread_attr_init(&padttr);
    if (ret != 0) {
        printf("pthread_attr_init failed: %d\n", ret);
        exit(-1);
    }

    // 线程属性联合体设置分离状态
    ret = pthread_attr_setdetachstate(&padttr, PTHREAD_CREATE_DETACHED);
    if (ret != 0) {
        printf("pthread_attr_setdetachstate failed: %d\n", ret);
        exit(-1);
    }

    // 使用以上线程属性联合体创建线程
    pthread_t pid;
    ret = pthread_create(&pid, &padttr, foo, NULL);
    if (ret != 0) {
        printf("pthread_create failed: %d\n", ret);
        exit(-1);
    }

    printf("main thread will exit\n");
    pthread_exit(NULL);
    
    return 0;
}