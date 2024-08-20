#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char *NODE_DATA_TYPE;

int main(int argc, char *argv[]) {
    NODE_DATA_TYPE data;
    data = (char *)malloc(6 * sizeof(char));
    memcpy(data, "hello", 6);
    printf("data: %s\n", data);
    return 0;
}