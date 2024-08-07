#include <stdio.h>

// 
void test() {
    int val = 10;
    /* constant pointer */
    const int* a = &val;
    int const *b = &val;
    // constant modification value
    // *a = 20; // 表达式必须是可修改的左值
    // *b = 20; // 表达式必须是可修改的左值

    /* pointer constant */
    int* const c = &val;
    // constant modification pointer
    // c = NULL; // 表达式必须是可修改的左值
}


int main() {

    return 0;
}