#include <iostream>

void foo(int &&a) {
    std::cout << "foo(int &&a)" << std::endl;
    a = 20;
}

void foo(const int &a) {
    std::cout << "foo(const int &)" << std::endl;
}

void foo(int &a) {
    std::cout << "foo(int &)" << std::endl;
}

int main(int argc, char const *argv[]) {
    int a = 10;
    foo(a);
    foo(std::move(a));
    foo(10);
    std::cout << a << std::endl;
    return 0;
}