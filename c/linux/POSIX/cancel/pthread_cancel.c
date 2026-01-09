/*
#include <pthread.h>

// 取消指定线程的执行，发送取消请求
// 发送成功不代表线程停止了
int pthread_cancel(pthread_t thread);
    // parameter:
        - thread: 指定的线程

    // return:
        - 成功返回 0，失败返回错误码
 */

#include <pthread.h>
#include <stdio.h>

void *foo(void *arg) {
    while (1) {
        printf("foo\n");
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t pid;
    pthread_create(&pid, NULL, foo, NULL);
    pthread_cancel(pid);
    void *ret = NULL;
    pthread_join(pid, &ret);
    if (ret == PTHREAD_CANCELED) {
        printf("thread was canceled\n");
    } else {
        printf("thread was not canceled\n");
    }
    return 0;
}