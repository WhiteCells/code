#include <iostream>

class B;

class A {
    friend class B;
private:
    int x = 1;
    const int y = 2;
    static const int z = 3;
};

class B {
public:
    void foo() {
        std::cout << a.x << a.y << a.z << std::endl;
        a.x = 2;
        std::cout << a.x << a.y << a.z << std::endl;
    }
private:
    A a;
};

int main(int argc, char const *argv[]) {
    B b;
    b.foo();
    return 0;
}