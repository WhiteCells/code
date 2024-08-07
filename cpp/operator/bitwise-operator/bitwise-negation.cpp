// ~
#include <iostream>

void UseNegation() {
    std::cout << (unsigned long long)(~0) << '\n';
    std::cout << ULLONG_MAX << '\n';
    std::cout << (unsigned long)(~0) << '\n';
    std::cout << ULONG_MAX << '\n';
    std::cout << (unsigned int)(~0) << '\n';
    std::cout << UINT_MAX << '\n';
    int a = 0b10101;
    int b = 12;
    int c = 012;
    int d = 0x1a;
    std::cout << a << ' ' << b << ' ' << c << ' ' << d << '\n';
}

int main() {
    UseNegation();
    return 0;
}