#include <string.h>
#include <stdio.h>

void foo() {
    char buf[1024];
    memset(buf, 0, sizeof(buf));
    memset(buf, -1, sizeof(buf));
    // memset(buf, 1, sizeof(buf)); // ?
}

int main(int argc, char *argv[]) {
    foo();
    return 0;
}