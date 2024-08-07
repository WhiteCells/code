#include <iostream>

// C++11
auto func1(auto a, auto b) -> decltype(a + b) {
    return a + b;
}

auto func2(auto a, int b) { // C++14
    return a + b;
}

auto foo2() {
    return 1;
    return 1.1;
}

int main(int argc, char const *argv[]) {
    std::cout << func1(1, 2.2);
    return 0;
}