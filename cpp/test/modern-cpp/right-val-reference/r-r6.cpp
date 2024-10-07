#include <iostream>

class A {
public:
    A() : c(new char('a')) {
        std::cout << "A()" << std::endl;
    }
    A(const A &other) {
        std::cout << "A(const A &)" << std::endl;
        c = other.c;
    }
    A(A &&other) {
        std::cout << "A(A &&)" << std::endl;
        c = other.c;
    }
    ~A() {
        std::cout << "~A()" << std::endl;
        if (c != nullptr) {
            delete c;
            c = nullptr;
        }
    }
    char *c;
};

A foo(A &&a) {
    a.c = new char('b');
    return std::move(a);
}

int main(int argc, char const *argv[]) {
    // A &&a = std::move(A());
    // std::cout << "---" << std::endl;
    return 0;
}