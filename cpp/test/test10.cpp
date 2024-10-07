// // #include <stdio.h>
// // #include <algorithm>

// // void foo(int *arr1, int *arr2, int *arr3, int len) {
// //     for (int i = 0, j = 0, k = 0; i < len && j < len && k < len;) {
// //         if (arr1[i] == arr2[j] && arr2[j] == arr3[k]) {
// //             printf("%d\n", arr1[i]);
// //             ++i, ++j, ++k;
// //             continue;
// //         }
// //         int max_num = std::max(arr1[i], std::max(arr2[j], arr3[k]));
// //         i += arr1[i] < max_num;
// //         j += arr2[j] < max_num;
// //         k += arr3[k] < max_num;
// //     }
// // }

// // int main(int argc, char *argv[]) {
// //     int arr1[3] = {1, 2, 3};
// //     int arr2[3] = {2, 3, 4};
// //     // int arr3[3] = {-1, 0, 2};
// //     int arr3[3] = {3, 4, 5};
// //     foo(arr1, arr2, arr3, 3);
// //     return 0;
// // }

// #include <iostream>

// enum LongLongEnum : long long {
//     x1,
//     x2
// };

// struct LongLongStruct {
//     long long x1 : 8;
//     long long x2 : 24;
//     long long x3 : 32;
// };

// int main(int argc, char *argv[]) {
//     // std::cout << sizeof(LongLongStruct) << std::endl;    // 8
//     // std::cout << sizeof(LongLongEnum) << std::endl;      // 8
//     // std::cout << sizeof(LongLongEnum::x1) << std::endl;  // 8
//     // std::cout << sizeof(LongLongEnum::x2) << std::endl;  // 8

//     long long x1 = 1 << 32; // 1 作为 32 位整数操作（可能会警告，溢出）
//     std::cout << x1 << std::endl; // 0

//     long long x2 = 1LL << 32; // 1 作为 64 位整数操作
//     std::cout << x2 << std::endl; // 0x100000000s
//     return 0;
// }