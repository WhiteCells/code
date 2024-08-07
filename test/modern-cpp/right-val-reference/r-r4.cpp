#include <iostream>

class A {
public:
    A() {}
    int x = 10;
};

void foo(const A &a) {
    std::cout << "foo(const A &a)" << std::endl;
}

void foo(A &a) {
    std::cout << "foo(A &a)" << std::endl;
}

void foo(A &&a) {
    std::cout << "foo(A &&)" << std::endl;
}

void test() {
    foo(A());
}

int main(int argc, char const *argv[]) {
    test();
    return 0;
}