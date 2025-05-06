#include <iostream>

struct A {
    int x = 1;
};

void foo(const A &a) {
    std::cout << "foo(const A &a)" << std::endl;
}

void foo(A &&a) {
    std::cout << "foo(A &a)" << std::endl;
    a.x = 2;
}

int main(int argc, char const *argv[]) {
    foo(A());
    A a;
    foo(a);
    std::cout << a.x << std::endl;
    const A a2 = a;
    foo(a2);
    const A &a3 = a;
    foo(a3);
    return 0;
}