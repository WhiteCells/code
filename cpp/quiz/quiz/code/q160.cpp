#include <iostream>

struct A {
    virtual void foo(int a = 1) {
        std::cout << "A" << a;
    }
};

// 结构体只能继承结构体
// 类只能继承类
struct B : A {
    virtual void foo(int a = 2) {
        std::cout << "B" << a;
    }
};

int main() {
    A *b = new B;
    b->foo();
    return 0;
}