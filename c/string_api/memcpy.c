#include <string.h>
#include <stdio.h>

void foo() {
    short id;
    short id_num = 10;
    memcpy(&id, &id_num, sizeof(id_num));
    printf("id: %d\n", id);
}

int main(int argc, char *argv[]) {
    foo();
    return 0;
}