#include <iostream>

struct A {
    A() { std::cout << "A()" << std::endl; }
    A(const A &) { std::cout << "A(const A &)" << std::endl; }
    A(A &&) { std::cout << "A(A &&)" << std::endl; }
    A &operator=(const A &) {
        std::cout << "operator=(const A &)" << std::endl;
        return *this;
    }
    A &operator=(A &&) {
        std::cout << "operator=(A &&)" << std::endl;
        return *this;
    }
    ~A() { std::cout << "~A()" << std::endl; }
};

int main(int argc, char const *argv[]) {
    // A &&a = A();
    A a = A();
    A a2 = a;
    std::cout << "---" << std::endl;
    return 0;
}