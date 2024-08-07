#include <iostream>

class A;

class B {
public:
    void visit(A &);
};

class A {
    friend void B::visit(A &);
private:
    int x = 1;
    const int y = 2;
    static const int z = 3;
};

void B::visit(A &a) {
    std::cout << a.x << a.y << a.z << std::endl;
    a.x = 2;
    std::cout << a.x << a.y << a.z << std::endl;
}

int main(int argc, char const *argv[]) {
    B b;
    A a;
    b.visit(a);
    return 0;
}