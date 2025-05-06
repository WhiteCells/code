#include <iostream>

class A {
public:
    A() { std::cout << "A()" << std::endl; }
    A(A &&) {}; // note
    A(const A &) = delete;
    A &operator=(const A &) = delete;
};

class B {
public:
    // B(A a) : a_(std::move(a)) { std::cout << __func__ << std::endl; }
    B(A &a) : a_(std::move(a)) { std::cout << __func__ << std::endl; }
    
private:
    A a_;
};

int main(int argc, char *argv[]) {
    A a;
    // B b1(std::move(a));
    B b2(a);
    return 0;
}