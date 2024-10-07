#include <iostream>

struct C {
    C();
    int i;
};

C::C() = default;

int main() {
    const C c;
    std::cout << c.i;
}