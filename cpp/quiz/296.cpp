#include <iostream>

struct S {
    int one;
    int two;
    int three;
};


int main() {
    S s{ 1, 2 };
    std::cout << s.one;
    std::cout << s.two;
    std::cout << s.three;
    return 0;
}