#include <iostream>

class Base {
public:
    virtual void foo() {
        std::cout << "Base::foo" << std::endl;
    }
    virtual ~Base() {}
};

class Derive1 : public Base {
public:
    void foo() {
        std::cout << "Derive1::foo" << std::endl;
    }
};

class Derive2 : public Base {
public:
    void foo() {
        std::cout << "Derive2::foo" << std::endl;
    }
};

int main() {
    Base *base = new Derive1();
    base->foo();
    base = new Derive2();
    base->foo();
    
    delete base;
    return 0;
}