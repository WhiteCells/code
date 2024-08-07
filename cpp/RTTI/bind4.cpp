#include <iostream>

class A {
public:
    virtual void foo() {
        std::cout << "A::foo" << std::endl;
    }

    virtual ~A() {}
};

class B {
public:
    virtual void foo() {
        std::cout << "B::foo" << std::endl;
    }
};

class C : public B, public A {
public:
    virtual void foo() override {
        std::cout << "C::foo" << std::endl;
    }
};

int main() {
    std::cout << sizeof(C) << std::endl;

    A *a = new C();
    a->foo();

    delete a;
    return 0;
}