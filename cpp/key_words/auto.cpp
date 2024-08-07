#include <iostream>


void UseAuto() {
    int a = 10;
    auto& b = a;
    b = 20;
    std::cout << a << '\n';
}

int main() {
    UseAuto();
    return 0;
}