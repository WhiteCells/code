#include <string.h>
#include <stdio.h>

void foo() {
    char buf[1024];
    bzero(buf, sizeof(buf));
}

int main(int argc, char *argv[]) {
    foo();
    return 0;
}