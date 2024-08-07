#include <iostream>

class A {
public:
    A(int x) {}
};

class B {
public:
    explicit B(int x) {}
};

class C {
public:
    C(int x, int y) {}
};

class D {
public:
    explicit D(int x, int y) {}
};

void foo(A a, B b, C c, D d) {}

int main(int argc, char *argv[]) {
    A a = 1;
    // B b = 1;
    B b = B(1);
    C c = {1, 1};
    // D d = {1, 1}; // error
    D d = D(1, 2);

    foo(1, B(1), {1, 1}, D(1, 2));
    
    return 0;
}