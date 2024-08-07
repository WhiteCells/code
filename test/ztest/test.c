#include <stdio.h>

#define PRINT(format, ...) \
    printf(format, ##__VA_ARGS__); \

int main(int argc, char *argv[]) {
    PRINT("test%s", "t");
    // printf("test");
    return 0;
}

#include <stdio.h>

int main(int argc, char *argv[]) {
    int arr[5] = {1, 2, 3, 4, 5};
    for (int i = 0; i < 5; ++i) {
        printf("%d ", i[arr]);
    }
    return 0;
}