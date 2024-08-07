#include <iostream>

namespace A {
extern "C" { int x; }
};

namespace B {
extern "C" { int x; } // symbol `x` is already defined
};

int A::x = 0;

int main() {
    std::cout << B::x;
    A::x=1;
    std::cout << B::x;
}