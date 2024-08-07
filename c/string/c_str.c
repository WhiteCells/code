#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *getChatStr() {
    const char *buf = "hello";
    return buf;
}

void initChar(char *buf) {
    buf = (char *)malloc(sizeof(char) * 10);
}

void test1() {
    const char str1[] = {"hello"};
    char str2[] = "hello";
    str2[0] = '0'; // 修改字面量是 ub

    const char *str3 = "hello";
    char *const str4 = {"hello"};
    const char *const str5 = "hello";
    char *str6 = "hello";

    printf("str1: %s\n", str1);
    printf("str2: %s\n", str2);
    printf("str3: %s\n", str3);
    printf("str4: %s\n", str4);
}

void test2() {
    printf("%s\n", getChatStr());
    char *buf = NULL;
    initChar(buf);
    printf("%s\n", buf); // error
}

void test3(const char *message) {
    const char *msg = message;
    printf("%s\n", msg);
}

char *strcpy1(char *dst, const char *src) {
    char *begin = dst;
    // while (((*dst++) = (*src++)) != '\0') {}
    while (*src != '\0') {
        *dst = *src;
        ++dst;
        ++src;
    }
    return begin;
}

void test4() {
    char *src = "message";
    char buf[strlen(src) + 1];
    memset(buf, 0, sizeof(buf));
    char *res = strcpy1(buf, src);
    printf("%s\n", res);
}

void test5(const char *buf) {
    printf("%ld\n", strlen(buf));
}

void test6() {
    test5("nihao");
}

int main(int argc, char *argv[]) {
    // test2();
    // test3("ceshi");
    // test4();

    // char buf[10];
    // printf("%d\n", sizeof(buf));

    // int ints[10];
    // printf("%d\n", sizeof(ints));

    test6();

    return 0;
}