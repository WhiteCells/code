#include <stdio.h>

typedef void (*FuncPtr)(void *);

typedef struct {
    FuncPtr func;
    void *arg;
} BoundFunction;

void callFunc(BoundFunction *boundfunc) {
    boundfunc->func(boundfunc->arg);
}

void print(void *arg) {
    int *val = (int *)arg;
    printf("%d\n", *val);
}

int main(int argc, char *argv[]) {
    int val = 1;
    BoundFunction func = {print, &val};
    callFunc(&func);
    return 0;
}