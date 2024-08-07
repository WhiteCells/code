#include <iostream>

// class A {};
void test1() {
    // int i = 10;
    // std::cout << typeid(i).name() << std::endl;

    // int *pi = &i;
    // std::cout << typeid(*pi).name() << std::endl;

    // A a;
    // std::cout << typeid(a).name() << std::endl;

    // A *pa = &a;
    // std::cout << typeid(*pa).name() << std::endl;
}

class Base {
public:
    virtual ~Base() {}
};

class Derive : public Base {
public:
    
};

int main() {
    Base *base = new Derive;
    std::cout << typeid(*base).name() << std::endl;
    if (typeid(*base) == typeid(Derive)) {
        std::cout << "is same" << std::endl;
    }
    delete base;
    return 0;
}