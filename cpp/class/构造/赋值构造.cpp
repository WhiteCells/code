#include <iostream>

class A {
public:
    A() {
        std::cout << "A()" << std::endl;
    }
    A(const A &a) {
        std::cout << "A(const A &a)" << std::endl;
    }
    A(A &&a) {
        std::cout << "A(&& a)" << std::endl;
    }
    ~A() {
        std::cout << "~A()" << std::endl;
    }
    A &operator=(const A &a) {
        std::cout << "operator=(const A &a)" << std::endl;
        return *this;
    }
};

void foo(A a) {
}

int main(int argc, char const *argv[]) {
    A a;
    foo(std::move(a));
    return 0;
}