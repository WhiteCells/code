/*
// 创建线程
#include <pthread.h>

int pthread_create(pthread_t *restrict thread,
                    const pthread_attr_t *restrict attr,
                    void *(*start_routine)(void *),
                    void *restrict arg);
    // parameter:
        - thread: 传出参数，创建线程成功后返回的线程 ID
        - attr: 线程属性联合体，为 NULL 则使用默认属性
        - start_routine: 线程函数地址
        - arg: 线程函数的参数

    // return:
        - 成功返回 0，失败返回 errno，并且 *thread 内容未定义
 */

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

struct A {
    int val;
};

void *foo(void *arg) {
    struct A *a = (struct A *)arg;
    printf("%d\n", a->val);
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t pid;
    struct A a;
    a.val = 10;
    pthread_create(&pid, NULL, foo, (void *)&a);

    sleep(1);
    return 0;
}