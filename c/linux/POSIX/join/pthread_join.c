/*
#include <pthread.h>

// 等待指定线程结束
int pthread_join(pthread_t thread, void **retval);
    // parameter:
        - thread: 等待线程的 ID
        - retval: 通常设置为 NULL，
                  如果非空则 pthread_join 复制一份线程退出值到一个内存区域，
                  并让 *__thread_return 指向该内存区域

    // return:
        - 成功返回 0，失败返回 errno
 */

#include <stdio.h>
#include <pthread.h>

typedef struct A {
    int val;
} A;

void *foo(void *arg) {
    A *a = (A *)(arg);
    printf("%d\n", a->val);
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t pid;
    A a;
    a.val = 1;
    pthread_create(&pid, NULL, foo, (void *)&a);
    pthread_join(pid, NULL);
    return 0;
}