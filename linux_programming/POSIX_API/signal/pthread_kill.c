/*
#include <signal.h>

// 给指定线程发送信号
int pthread_kill(pthread_t thread, int sig);
    // parameter:
        - thread: 线程 ID
        - sig: 信号

    // return:
        - 成功返回 0，失败返回错误码，并且不发送信号
          ESRCH：线程不存在
          EINVAL：信号不合法
 */

#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

static void onSignalTerm(int sig) {
    printf("sub thread will exit\n");
    pthread_exit(NULL);
}

void *foo(void *arg) {
    // 注册信号处理函数，放在首行
    signal(SIGQUIT, onSignalTerm);
    printf("sub thread start\n");
    while (1) {
        printf("sub thread\n");
        sleep(1);
    };
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t pid;
    int ret;

    ret = pthread_create(&pid, NULL, foo, NULL);
    if (ret != 0) {
        printf("%s\n", strerror(ret));
    }

    ret = pthread_kill(pid, SIGQUIT);
    if (ret != 0) {
        printf("%s\n", strerror(ret));
    }

    sleep(2);

    ret = pthread_join(pid, NULL);
    if (ret != 0) {
        printf("%s\n", strerror(ret));
    }

    return 0;
}