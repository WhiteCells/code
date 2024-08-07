#include <iostream>

class A {
public:
    A() { std::cout << __func__ << std::endl; }
    // ~A() { std::cout << __func__ << std::endl; }
    virtual ~A() { std::cout << __func__ << std::endl; }
    virtual void foo() = 0;
};

class B : public A {
public:
    B() { std::cout << __func__ << std::endl; }
    ~B() { std::cout << __func__ << std::endl; }
    virtual void foo() override {}
};

int main(int argc, char *argv[]) {
    {
        B lb;
        std::stoi()
    }
    std::cout << "---" << std::endl;
    A *b = new B();
    delete b;
    return 0;
}