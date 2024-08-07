#include <iostream>

class A {
public:
    // A() {}; // x requires a default value otherwise const A a2 will report an error
    int x = 1;
    const int y = 2;
};

int main(int argc, char const *argv[]) {
    A a1;
    a1.x = 10;
    std::cout << a1.x << std::endl;
    std::cout << a1.y << std::endl;

    const A a2;
    // a2.x = 10; // compilation failed
    std::cout << a2.x << std::endl;
    std::cout << a2.y << std::endl;
    return 0;
}