#include <iostream>

class Base {
public:
    virtual void foo() {
        std::cout << "Base::foo" << std::endl;
    }

    virtual ~Base() {}
};

class Derive : public Base {
public:
    void foo() override {
        std::cout << "Derive::foo" << std::endl;
    }

    virtual void foo2() {
        std::cout << "Derive::foo2" << std::endl;
    }
};

int main() {
    Base *base = new Derive;

    void **vfptr = *(void ***)base;

    // [0] &Base::foo
    // [1] &Base::~Base
    // [2] &Derive::foo
    // [3] &Derive::foo2
    void (*vf)() = (void(*)())vfptr[3];

    vf();

    delete base;
    return 0;
}