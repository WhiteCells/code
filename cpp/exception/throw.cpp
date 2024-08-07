#include <iostream>

int divide(int x, int y) {
    if (y == 0) {
        throw y; // 抛异常
    }
    return x / y;
}

void callDivide() {
    try {
        divide(10, 0);
    } catch (int e) {
        std::cout << "dividend by 0" << std::endl;
    }
}

int main() {
    callDivide();
    return 0;
}