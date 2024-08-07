#include <stdio.h>

typedef union X {
    int a;
    float b;
    char c;
    double d;
}X;

int main(int argc, char *argv[]) {
    X x;
    printf("%d\n", x.a);
    printf("%d\n", x.b);
    printf("%d\n", x.c);
    printf("%d\n", x.d);
}