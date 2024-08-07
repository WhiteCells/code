#include <iostream>

int main() {
    int a = 10;
    int b = 20;
    int x;
    x = a, b; // , 优先级最低
    std::cout << x << std::endl; // 10
}