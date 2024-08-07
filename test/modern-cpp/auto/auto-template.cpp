#include <iostream>

template<auto N> // C++17
void foo() {
    std::cout << N << std::endl;
}

int main() {
    foo<1>();
    foo<1.1>(); // compilation failed
    foo<'c'>();
    return 0;
}