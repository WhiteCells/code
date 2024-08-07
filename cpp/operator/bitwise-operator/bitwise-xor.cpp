// ^
#include <iostream>

void UseXOR() {
    // different return 1
    std::cout << (0 ^ 0) << '\n'; // 0
    std::cout << (1 ^ 1) << '\n'; // 0
    std::cout << (1 ^ 0) << '\n'; // 1
    std::cout << (1 ^ 1) << '\n'; // 1
}

int main() {
    UseXOR();
    return 0;
}