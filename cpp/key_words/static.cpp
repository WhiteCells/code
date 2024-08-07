#include <iostream>

class A {
public:
    A() { foo(); }

private:
    static const int a = 10;
    const int b = 20;

    static void help1() {}
    void help2() {}

    static void foo() {
        std::cout << a << std::endl;
        // std::cout << b << std::endl;

        help1();
        // help2();
    }
};

int main() {

}