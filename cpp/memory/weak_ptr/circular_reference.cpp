#include <memory>
#include <iostream>

class B;

class A {
public:
    A() { std::cout << __func__ << std::endl; }
    ~A() { std::cout << __func__ << std::endl; }

    std::shared_ptr<B> ptr_B;
};

class B {
public:
    B() { std::cout << __func__ << std::endl; }
    ~B() { std::cout << __func__ << std::endl; }

    std::shared_ptr<A> ptr_A;
};

void test_CircularReference() {
    A a;
    a.ptr_B = std::make_shared<B>();

    B b;
    b.ptr_A = std::make_shared<A>();
}

int main(int argc, char *argv[]) {
    test_CircularReference();
    return 0;
}