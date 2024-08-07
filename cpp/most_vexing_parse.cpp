#include <iostream>

// 最令人困惑的解析（most vexing parse）

class A {
public:
    A(int x) : x_(x) {}
private:
    int x_;
};

class B {
public:
    B() {}
};

int main(int argc, char *argv[]) {
    std::cout << sizeof(A()) << std::endl; // 解析为函数类型
    std::cout << sizeof(B()) << std::endl; // 解析为函数类型

    std::cout << sizeof(A {1}) << std::endl; // A 类的实例，C++11
    std::cout << sizeof(B {}) << std::endl;  // B 类的实例，C++11

    std::cout << sizeof(A) << std::endl; // A 类
    std::cout << sizeof(B) << std::endl; // B 类
    return 0;
}