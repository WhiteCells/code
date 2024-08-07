#include <iostream>

class A {
public:
    int x = 1;
    static int y;
    static const int z = 3;
};

int A::y = 2;

int main(int argc, char const *argv[]) {
    // class name access
    std::cout << A::y << std::endl;
    std::cout << A::z << std::endl;

    // object access
    A a;
    std::cout << a.y << std::endl;
    std::cout << a.z << std::endl;

    return 0;
}