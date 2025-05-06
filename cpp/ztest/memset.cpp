#include <iostream>
#include <string.h>

int main(int argc, char *argv[]) {
    int arr[10];
    memset(arr, 2, sizeof(arr));
    for (int i = 0; i < 10; ++i) {
        std::cout << arr[i] << std::endl;
    }

    int arr2[10];
    bzero(arr2, sizeof(arr2));
    for (int i = 0; i < 10; ++i) {
        std::cout << arr2[i] << std::endl;
    }
    return 0;
}