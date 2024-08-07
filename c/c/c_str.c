#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// 只可以修改 *str
// str 修改的实参并不修改
char *strcpy_(char *str, const char *src) {
    assert(src);
    char *dest = str;
    while ((*str++ = *src++) != '\0') {}
    return dest;
}

void copy(char **str) {
    *str = NULL;
}

int main() {
    // char *str = (char *)malloc(10 * sizeof(char));
    // strcpy_(str, "NULL");
    // printf("%s\n", str);

    char *str2 = "NULL";
    copy(&str2);
    if (str2) {
        printf("%s\n", str2);
    } else {
        printf("str2 is null\n");
    }
    return 0;
}