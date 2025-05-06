#include <iostream>
#include <cassert>

auto func(int a, int b) { // C++14
    return a + b;
}

auto f = [](auto a, auto b) { return a + b; }; // C++14

int main(int argc, char const *argv[]) {
    std::cout << func(1.1, 2) << '\n';
    std::cout << f(1, 2.2) << '\n';
    assert(true);
    assert(false);
    return 0;
}