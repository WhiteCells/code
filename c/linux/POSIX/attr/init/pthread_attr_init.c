/*
#include <pthread.h>

// 初始化的线程属性联合体
int pthread_attr_init(pthread_attr_t *attr);
    // parameter:
        - attr: 需要初始化的线程属性联合体

    // return:
        - 成功返回 0，失败返回错误码
 */

#include <pthread.h>

int main() {
    pthread_attr_t thread_t;
    int ret = pthread_attr_init(&thread_t);
}