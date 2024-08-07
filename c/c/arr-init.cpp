#include <iostream>

template<typename T>
void print(T p, int n);

int a[10]; // 全局变量数组, 默认初始化为 0

const int n = 10;
int b[n]; // 全局变量数组, 默认初始化为 0

int n2 = 10;
// int c[n2]; // error

void foo() {
    int arr1[100];             // 默认初始化为不确定的值
    // print(arr1, 100);

    int arr2[100] = {};        // 全部初始化为 0
    // print(arr2, 100);

    int arr3[100] = {0};     // 全部初始化为 0
    // print(arr3, 100);

    int arr4[100] = {100};   // arr4[0] = 100, 其他全部初始化为 0
    // print(arr4, 100);

    static int arr5[100];      // 静态局部变量数组, 默认初始化为 0
    // print(arr5, 100);
}

class MyClass {
public:
    int arr_[100];         // 成员变量数组，默认初始化为不确定的值
    static int s_arr_[10]; // 静态成员变量数组，默认初始化为 0
};

int MyClass::s_arr_[10];

int main() {
    foo();
    MyClass mc;
    print(mc.arr_, 100);
    print(MyClass().arr_, 100); // 未显式初始化，则成员会被初始化为默认值
    print(MyClass::s_arr_, 100);
    return 0;
}

template<typename T>
void print(T p, int n) {
    for (int i = 0; i < n; ++i) {
        std::cout << *(p + i) << ' ';
    }
    std::cout << std::endl;
}