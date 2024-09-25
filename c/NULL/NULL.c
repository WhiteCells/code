#include <stdio.h>

void foo(int *) { printf("int *"); }
// void foo(const int *) { printf("const int *"); }

int main(int argc, char *argv[]) {
    // foo(0);
    foo(1);
    return 0;
}