#include <iostream>

int a = 1;
int &ra = a;
// int &x = 1; // compilation failed
const int &x = 1;

class A {
public:
    A() {}
    A(const A &) {}
    A &operator=(const A &) { return *this; }
};

A makeA() {
    return A();
}
void test1() {
    A a;
    A a2(a);
    A a3(makeA());
    a3 = makeA();
}

void foo(const int &a) {
    std::cout << "foo(const int &)" << std::endl;
}

void test2() {
    int x = 0;
    foo(x);
    int &rx = x;
    foo(rx);
    const int y = 1;
    foo(y);
    const int &ry = y;
    foo(ry);
}

void foo(int &a) {
    std::cout << "foo(int &)" << std::endl;
}

void test3() {
    int x = 0;
    foo(x);
    const int y = 0;
    foo(y);
}

int main() {
    // test1();
    // test2();
    test3();
    return 0;
}