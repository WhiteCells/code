/*
#include <pthread.h>

// 弹出栈顶清理函数，并选择是否执行清理函数 
void pthread_cleanup_pop(int execute);
    // parameter:
        - execute: 选择弹出栈顶清理函数的同时，是否执行清理函数
                   非 0 时表示执行清理函数
 */

#include <pthread.h>
#include <stdio.h>

void cleanup(void *arg) {

}

void *foo(void *arg) {
    pthread_cleanup_push(foo, NULL);

    pthread_cleanup_pop(0);
}

int main(int argc, char *argv[]) {
    
    return 0;
}