#include <iostream>

#define ARR_LEN 1000

int main(int argc, char *argv[]) {

    int *arr = new int[ARR_LEN];
    for (int i = 0; i < ARR_LEN; ++i) {
        std::cout << *(arr + i) << " ";
    }
    std::cout << std::endl;

    // int arr2[ARR_LEN];
    int arr2[ARR_LEN] {};
    for (int i = 0; i < ARR_LEN; ++i) {
        std::cout << *(arr2 + i) << " ";
    }
    std::cout << std::endl;
    return 0;
}