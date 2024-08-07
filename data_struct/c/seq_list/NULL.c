#include <stdio.h>

int main(int argc, char *argv[]) {
    int *p = NULL;
    if (p == NULL) {
        return 1;
    }
    printf("%d\n", *p);
    return 0;
}