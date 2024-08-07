#include <stdio.h>

void  __nonnull((1, 3)) foo(int *a, int *b, int *c, int *d) {
    if (a) {
        printf("%d ", *a);
    }
    if (b) {
        printf("%d ", *b);
    }
    if (c) {
        printf("%d ", *c);

    }
    if (d) {
        printf("%d ", *d);
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    int a = 1, b = 2, c = 3, d = 4;
    foo(&a, NULL, NULL, NULL); // no warning

    printf("%d %d %d %d\n", a, b, c, d);
    return 0;
}