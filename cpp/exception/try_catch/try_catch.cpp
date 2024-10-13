#include <iostream>

class A {
public:
    A() { std::cout << __func__ << std::endl; }
    ~A() { std::cout << __func__ << std::endl; }
};

int main(int argc, char *argv[]) {
    try {
        A a;
        // throw 1;
    } catch (...) {
        A a;
    }
    return 0;
}