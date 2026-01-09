/*
#include <pthread.h>

// 让内核检查是否需要取消当前线程
void pthread_testcancel(void);
 */

#include <pthread.h>
#include <stdio.h>

void *foo(void *arg) {
    while (1) {
        printf("foo\n");
        pthread_testcancel();
    }
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