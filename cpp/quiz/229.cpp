#include <iostream>

int a = 1;

int main(int argc, char const *argv[]) {
    auto f = [](int b) {return a + b;};
    std::cout << f(4);
    return 0;
}