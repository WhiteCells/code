#include <iostream>

class A {
public:
    A() {}

    // void foo() const { std::cout << "const" << std::endl; }
    void foo() { std::cout << "non const" << std::endl; }
};

int main(int argc, char *argv[]) {
    A a;
    a.foo();

    const A ca;
    // ca.foo();
    return 0;
}