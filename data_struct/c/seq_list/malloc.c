#include <stdlib.h> /* for malloc() */
#include <stdio.h>

void foo(int *parameter) {
    parameter = NULL;
}

int main(int argc, char *argv[]) {
    int *ptr = (int *)malloc(sizeof(int));
    // p = 0;
    foo(ptr);
    // printf("%p\n", p);
    return 0;
}