#include <iostream>

/*

    A
   / \
  B   C
   \ /
    D
 */

class A {
public:
    A(int a) : a(a) {
        std::cout << "A(int a)" << std::endl;
    }
    int a;
};

class B : virtual public A {
public:
    B(int b) : A(0), b(b) {
        std::cout << "B(int a)" << std::endl;
    }
    int b;
};

class C : virtual public A {
public:
    C(int c) : A(1), c(c) {
        std::cout << "C(int a)" << std::endl;
    }
    int c;
};

class D : virtual public B, virtual public C {
public:
    D(int d) : B(1), C(2), d(d), A(0) {
        std::cout << "D(int a)" << std::endl;
    }
    int d;
};

int main(int argc, char *argv[]) {
    D d(3);
    std::cout << d.a << std::endl;
    // std::cout << d.B::a << std::endl;
    return 0;
}