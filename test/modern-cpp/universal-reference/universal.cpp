#include <iostream>

template<class T>
void foo(T &&t) {}

int getVal() { return 1; }
auto &&y = getVal();
auto &&z = getVal;

int main(int argc, char const *argv[]) {
    std::cout << z() << y << std::endl;
    return 0;
}