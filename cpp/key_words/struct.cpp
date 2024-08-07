#include <iostream>

struct Empty {};

void PrintEmptyStructSize() {
    std::cout << sizeof(Empty) << '\n';
}

struct A {
    int b;
    void foo() {}
};

struct B : A {
    void foo2() {
        foo();
        b = 1;
    }
};

struct C : public A {
    void foo3() {
        foo();
        b = 1;
    }
};

template<typename T>
struct D {
    void foo() {
        std::cout << typeid(T).name() << std::endl;
    }
};

int main() {
    PrintEmptyStructSize(); // 1
    D<int> d;
    d.foo();
    return 0;
}