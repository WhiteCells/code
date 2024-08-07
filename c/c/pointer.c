#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**************************************************/
void initPtr(int *p) {
    p = (int *)malloc(sizeof(int));
}

void test_initPtr() {
    int *p = NULL;
    initPtr(p);
    printf("argument: %p\n", p);
}

/**************************************************/
char *strcpy_(char *str, const char *src) {
    char *res = str;
    while ((*str++ = *src++) != '\0') {
    }
    return res;
}

void test_strcpy_() {
    char *str;
    // char str[5] = {};
    // strcpy(str, "hello");
    strcpy_(str, "hello");
    printf("%s\n", str);
}

/**************************************************/
void destroyPtr(int *p) {
    // 可以释放
    free(p);
    // 修改指向形参无法修改实参
    p = NULL;
}

void test_destroyPtr() {
    int *p = (int *)malloc(sizeof(int));
    *p = 1;
    printf("argument address: %p\n", p);
    printf("argument val: %d\n", *p);
    destroyPtr(p);
    printf("argument address: %p\n", p);
    printf("argument val: %d\n", *p);
}

/**************************************************/
#define A 1
// #define B 1
void printAddress(int *p) {
    printf("parameter: %p\n", p);
#ifdef A
    p = NULL;
    printf("parameter: %p\n", p);
#elif B
    *p = 10;
#endif
}

void test_printAddress() {
    int *p = (int *)malloc(sizeof(int));
    *p = 20;
    printf("argument: %p\n", p);
    printAddress(p);
    printf("argument: %p\n", p);
    printf("argument: %d\n", *p);
}

/**************************************************/
void doublePtr(int **p) {
    *p = (int *)malloc(sizeof(int));
    **p = 10;
}

void test_doublePtr() {
    int *ptr;
    printf("argument address: %p\n", ptr);
    // printf("argument val: %d\n", *ptr);
    doublePtr(&ptr);
    printf("argument address: %p\n", ptr);
    printf("argument val: %d\n", *ptr);
}
/**************************************************/

int main(int argc, char *argv[]) {
    // test_initPtr();
    // test_destroyPtr();
    // test_printAddress();
    test_doublePtr();
    return 0;
}