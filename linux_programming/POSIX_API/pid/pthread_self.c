/*
#include <pthread.h>

// 获取当前线程 ID
pthread_t pthread_self(void);
    // return:
        - 这个函数一定成功
          返回线程 ID
 */

#include <pthread.h>
#include <stdio.h>

void *foo(void *arg) {
    printf("sub thread id: %ld\n", pthread_self());
    return NULL;
}

int main() {
    printf("currently thread id: %ld\n", pthread_self());

    pthread_t pid;
    pthread_create(&pid, NULL, foo, NULL);
    printf("sub thread id: %ld\n", pid);
    pthread_join(pid, NULL);
    pthread_exit(NULL);
}