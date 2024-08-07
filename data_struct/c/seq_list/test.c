#include <stdio.h>

// type define
typedef struct A {
    char c;
    int a;
} A;

int main(int argc, char *argv[]) {
    printf("%zu\n", sizeof(char)); // 1
    printf("%zu\n", sizeof(int)); // 4
    printf("%zu\n", sizeof(A));
    return 0;
}