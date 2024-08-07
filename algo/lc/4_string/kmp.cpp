#include <stdio.h>
#include <stdlib.h>

typedef struct String {
    char* data;
    int size;
}String;

// 初始化串
String* initString() {
    String* s = (String*)malloc(sizeof(String));
    s->data = NULL;
    s->size = 0;
    return s;
}

// 添加数据
void stringAssign(String* s, char* data) {
    if (s->data) {
        free(s->data);
    }
    int len = 0;
    char* temp = data;
    while (*temp) {
        len++;
        temp++;
    }

    if (len == 0) {
        len = 0;
        s->data = NULL;
    }
    else {
        temp = data;
        s->size = len;
        s->data = (char*)malloc(sizeof(char) * (len + 1));
        for (int i = 0; i < len; i++, temp++) {
            s->data[i] = *temp;
        }
    }
}

// 输出字符串结构
void printString(String* s) {
    for (int i = 0; i < s->size; i++) {
        printf(i == 0 ? "%c" : "->%c", s->data[i]);
    }
    printf("\n");
}

// 计算 next 数组
int* getNext(String* s) {
    int* next = (int*)malloc(sizeof(int) * s->size);
    int i = 0;
    int j = -1;
    next[i] = j;
    while (i < s->size - 1) {
        if (j == -1 || s->data[i] == s->data[j]) {
            i++;
            j++;
            next[i] = j;
        }
        else {
            j = next[j];
        }
    }
    return next;
}

// 输出 next 数组
void printNext(int* next, int len) {
    for (int i = 0; i < len; i++) {
        printf(i == 0 ? "%d" : "->%d", next[i] + 1);
    }
    printf("\n");
}

// kmp 算法
void kmpMatch(String* master, String* sub, int* next) {
    int i = 0;
    int j = 0;
    while (i < master->size && j < sub->size) {
        if (j == -1 || master->data[i] == sub->data[j]) {
            i++;
            j++;
        }
        else {
            j = next[j];
        }
    }
    if (j == sub->size) {
        printf("匹配成功");
    }
    else {
        printf("未匹配成功");
    }
}

int main() {

    String* s1 = initString();
    stringAssign(s1, "ABACCABABD");

    String* s2 = initString();
    stringAssign(s2, "CCAB");

    int* next = getNext(s2);
    printNext(next, s2->size);

    kmpMatch(s1, s2, next);

    return 0;
}