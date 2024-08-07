#include <iostream>

class Base1 {
public:
    virtual void foo() {} 
};

class Base2 {
public:
    virtual void foo() {}
};

class Derive : public Base1, public Base2 {
public:
    void foo() override {}
};

int main() {
    std::cout << sizeof(Derive) << std::endl;
    return 0;
}