#include <iostream>

struct A {
    ~A() { std::cout << "~A()" << std::endl; }
};

int main(int argc, char const *argv[]) {
    A();
    std::cout << "---" << std::endl;
    return 0;
}