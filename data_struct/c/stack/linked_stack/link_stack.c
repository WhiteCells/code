#include <stdio.h>
#include <stdlib.h>

typedef struct StackNode {
    int value;
    struct StakcNode *next;
} StackNode;

typedef struct LinkStack {
    int length;
    StackNode *head;
} LinkStack;

// 
int main(int argc, char *argv[]) {
    int *p = (int *)malloc(sizeof(int));
    int *tmp = p;

    p = (int *)malloc(sizeof(int));

    // free
    free(tmp);
    tmp = NULL;

    return 0;
}