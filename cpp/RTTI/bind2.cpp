#include <iostream>

class Base {
public:
    virtual void foo() {}
};

int main() {
    std::cout << sizeof(Base) << std::endl;
    return 0;
}