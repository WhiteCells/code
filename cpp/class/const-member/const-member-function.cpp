#include <iostream>

class A {
public:
    void foo() const;
    void foo();

    int x = 1;
    const int y = 2;
};

void A::foo() const {
    std::cout << "void foo() const;" << std::endl;
    std::cout << x << y << std::endl;
}

void A::foo() {
    std::cout << "void foo();" << std::endl;
    std::cout << x << y << std::endl;
}

int main(int argc, char const *argv[]) {
    A a1;
    a1.foo();

    const A a2;
    a2.foo();
    return 0;
}