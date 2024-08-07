#include <iostream>

class A {
public:
    A() { std::cout << __func__ << std::endl; }
    ~A() { std::cout << __func__ << std::endl; }
    // virtual ~A() { std::cout << __func__ << std::endl; }
};

class B : public A {
public:
    B() : A() { std::cout << __func__ << std::endl; }
    ~B() { std::cout << __func__ << std::endl; }
};

int main(int argc, char *argv[]) {
    // B b;
    A *a = new B();
    delete a;
    return 0;
}