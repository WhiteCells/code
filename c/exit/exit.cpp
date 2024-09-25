#include <stdlib.h>

void foo() {
    exit(1);
}

int main(int argc, char *argv[]) {
    foo();
    return 0;
}