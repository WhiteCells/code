/*
#include <pthread.h>

// 销毁线程属性联合体
int pthread_attr_destroy(pthread_attr_t *attr);
    // parameter:
        - attr: 需要销毁的线程属性联合体

    // return:
        - 成功返回 0，失败返回错误码
 */

#include <pthread.h>

int main() {
    pthread_attr_t pthread_attr;
    pthread_attr_init(&pthread_attr);

    pthread_attr_destroy(&pthread_attr);
    return 0;
}