#include <iostream>

class A {
    friend void foo() {
        std::cout << "foo" << std::endl;
        A a;
        std::cout << a.x << std::endl;
    }
private:
    A() : x(1) {}
    int x;
};

void foo();

int main(int argc, char *argv[]) {
    foo();
    return 0;
}