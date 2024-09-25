/*
#include <pthread.h>

// 获取线程分离状态值
int pthread_attr_getdetachstate(const pthread_attr_t *attr,
                                int *detachstate);
    // parameter:
        - attr: 需要获取分离状态的线程属性联合体
        - detachstate: 传出参数，线程属性联合体的分离状态值

    // return:
        - 成功返回 0，失败返回错误码
 */

#include <pthread.h>

void *foo(void *arg) {

}

int main() {

}