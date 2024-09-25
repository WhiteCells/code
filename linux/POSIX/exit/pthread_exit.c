/*
#include <pthread.h>

// 退出线程
[[noreturn]] void pthread_exit(void *retval);
    // parameter:
        - retval: 线程函数终止后通过 retval 记录返回值
                  使用 pthread_join 第二个参数接受
 */

#include <pthread.h>
#include <stdio.h>

void *foo(void *arg) {
    static int a = 10;
    pthread_exit((void *)&a);
}

int main(int argc, char *argv[]) {
    pthread_t tid;
    pthread_create(&tid, NULL, foo, NULL);

    int *ret = NULL;
    pthread_join(tid, (void **)&ret);
    printf("thread return: %d\n", *ret);
    return 0;
}