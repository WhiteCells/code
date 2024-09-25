#include <stdio.h>

typedef struct A {
    int x; // 4 byte
    int y; // 4 byte
    int z; // 4 byte
} A;

int main(int argc, char *argv[])
{
    printf("%ld\n", sizeof(A));
    return 0;
}