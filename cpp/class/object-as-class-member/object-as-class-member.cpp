#include <iostream>

class A {
public:
    int x = 1;
private:
    int y = 2;
};

class B {
public:
    void foo() {
        std::cout << a.x << std::endl;
    }
private:
    A a;
};

int main(int argc, char const *argv[]) {
    B b;
    b.foo();
    return 0;
}