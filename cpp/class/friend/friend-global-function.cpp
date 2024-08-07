#include <iostream>

class A {
    friend void foo(A &);
private:
    int x = 1;
    const int y = 2;
    static const int z = 3;
};

void foo(A &a) {
    std::cout << a.x << a.y << a.z << std::endl;
    a.x = 2;
    std::cout << a.x << a.y << a.z << std::endl;
}

int main(int argc, char const *argv[]) {
    A a;
    foo(a);
    return 0;
}