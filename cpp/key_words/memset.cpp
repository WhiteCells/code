#include <iostream>

#include <string.h>

// https://baike.baidu.com/item/memset/4747579?fr=ge_ala

auto print = [&](const int* arr, const int& n) {
    for (int i = 0; i < n; ++i) {
        std::cout << arr[i] << ' ';
    }
    std::cout << '\n';
};

// memset 函数按字节对内存块进行初始化，
// 所以不能用它将 int 数组初始化为 0 和 -1 之外的其他值（除非该值高字节和低字节相同）
void UseMemsetInitArr() {
    int n = 10;
    int arr1[n] {}; // variable-sized object may not be initiali
    print(arr1, n);

    int arr2[n];
    memset(arr2, 0, sizeof(arr2));
    print(arr2, n); // all 0

    int arr3[n];
    memset(arr3, -1, sizeof(arr3));
    print(arr3, n); // all -1

    int arr4[n];
    memset(arr4, 1, sizeof(arr4));
    print(arr4, n); // garbage data

}

int main() {
    UseMemsetInitArr();
    return 0;
}


