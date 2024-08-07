#include <stdio.h>

void foo(int *restrict a, int *restrict b) {
    ++(*a);
    ++(*b);
}

int main(int argc, char *argv[]) {
    int a = 1, b = 1;

    foo(&a, &b);
    printf("a: %d, b: %d\n", a, b); // 2 2

    foo(&a, &a); // ub
    printf("a: %d, b: %d\n", a, b);
    return 0;
}