#include <iostream>

class Base {
public:
    virtual void foo() {}
};

int main() {
    Base b1;
    void **b1_vfptr = *(void ***)&b1;

    Base b2;
    void **b2_vfptr = *(void ***)&b2;

    std::cout << b1_vfptr << std::endl;
    std::cout << b2_vfptr << std::endl;
    std::cout << (b1_vfptr == b2_vfptr) << std::endl;

    return 0;
}