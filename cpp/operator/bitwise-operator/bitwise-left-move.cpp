// <<
#include <iostream>

void Divide() {
    int divisor = 5; // 被除数
    int res = divisor >> 1;
    std::cout << res << '\n';
}

int main() {
    Divide();
    return 0;
}