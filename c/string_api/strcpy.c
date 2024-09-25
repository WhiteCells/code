#include <stdio.h>
#include <string.h>
#include <assert.h>

char *strcpy2(char *dest, const char *src) {
    char *beg = dest;
    while ((*beg++ = *src++) != '\0') {

    }
    return dest;
}

void foo(const char *src) {
    char buf[16];
    // strcpy(buf, src);
    strcpy2(buf, src);
    printf("%s\n", buf);
}

int main(int argc, char *argv[]) {
    foo("main");
    return 0;
}