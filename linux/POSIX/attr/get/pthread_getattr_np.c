/*
#define _GNU_SOURCE
#include <pthread.h>

// 获取线程属性
int pthread_getattr_np(pthread_t thread, pthread_attr_t *attr);
    // parameter:
        - pthread: 线程 ID
        - attr: 传出参数，返回线程属性联合体

    // return:
        - 成功返回 0，失败返回错误码

    // note:
        - 使用该函数前需要在 pthread.h 前定义宏 _GNU_SOURCE
 */

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <pthread.h>
#include <error.h>

void *foo(void *arg) {
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t pid;
    pthread_create(&pid, NULL, foo, NULL);

    // 定义线程属性联合体
    pthread_attr_t pattr;

    // 初始化线程属性联合体
    pthread_attr_init(&pattr);

    // 获取指定线程属性联合体
    pthread_getattr_np(pid, &pattr);

    // 销毁线程属性联合体
    pthread_attr_destroy(&pattr);

    return 0;
}