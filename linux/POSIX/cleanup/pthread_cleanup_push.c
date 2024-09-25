/*
#include <pthread.h>

// 将清理函数压栈
void pthread_cleanup_push(void (*routine)(void *), void *arg);
    // parameter:
        - routine: 清理函数的指针
        - arg: 清理函数的参数
 */

#include <pthread.h>
#include <stdio.h>

void cleanup(void *arg) {
    printf("cleanup\n");
}

void *foo(void *arg) {
    pthread_cleanup_push(cleanup, NULL);
    // return NULL;
    // pthread_exit(NULL);
    // while (1) { pthread_testcancel(); }
    // pthread_cleanup_pop(1);
    pthread_cleanup_pop(0);
}

int main(int argc, char *argv[]) {
    pthread_t pid;
    pthread_create(&pid, NULL, foo, NULL);
    pthread_detach(pid);
    return 0;
}