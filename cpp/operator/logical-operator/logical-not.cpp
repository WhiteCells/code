// !
#include <iostream>

void foo() {
    int a = 1;
    a = !a;
    std::cout << a << '\n';
}

int main() {
    foo();
    return 0;
}