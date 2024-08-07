#include <iostream>

class Base {
public:
    virtual void foo() {}
};

class Derive : public Base {
public:
    void foo() override {}
};

int main() {
    Base *b1 = new Derive();
    void **b1_vfptr = *(void ***)b1;

    Base *b2 = new Derive();
    void **b2_vfptr = *(void ***)b2;

    std::cout << (b1_vfptr == b2_vfptr) << std::endl;

    return 0;
}