#include <stdio.h>
#include <assert.h>

char *strcpy2(char *str, const char *src) {
    char *dest = str;
    while ((*dest++ = *src++) != '\0') {}
    return str;
}

int main() {
    char buf[16];
    strcpy2(buf, "123456");
    printf("%s\n", buf);
    return 0;
}