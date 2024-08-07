#include <iostream>

class B;

class A {
public:
    // friend class B;
    int x = 1;
private:
    friend class B; // friend 不受访问限制符影响
    int y = 2;
};

class B {
public:
    B() {
        std::cout << a.x << std::endl;
        std::cout << a.y << std::endl;
    }
    A a;
};

int main(int argc, char *argv[]) {
    B b;
    return 0;
}