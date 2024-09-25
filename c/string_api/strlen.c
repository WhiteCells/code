#include <stdio.h>
#include <string.h>

size_t strlen2(const char *str) {
    size_t len = 0;
    while (*str++ != '\0') {
        ++len;
    }
    return len;
}

void foo(const char *str) {
    printf("strlen %ld\n", strlen(str));
    printf("strlen %ld\n", strlen2(str));
}

int main(int argc, char *argv[]) {
    foo("main");
    return 0;
}