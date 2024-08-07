#include <iostream>

void UseAdd() {
    char c = '1';
    char d = '2';
    char e = c + d;
    std::cout << c << '\n';
    std::cout << d << '\n';
    std::cout << c - '0' << '\n';
    std::cout << e << '\n';
}

int main() {
    UseAdd();
    return 0;
}