#include <stdio.h>

// 形参无法改变实参
// 形参是实参的一份拷贝
// a 就是形参
void foo(int a) {
    a = 20;
}

int main(int argc, char *argv[]) {
    int x = 10;
    // x 就是实参
    foo(x);
    printf("%d\n", x);
    return 0;
}