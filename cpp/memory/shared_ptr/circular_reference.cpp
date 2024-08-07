#include <iostream>
#include <memory>

class B;

class A {
public:
    A() {}
    ~A() {
        std::cout << __func__ << std::endl;
    }
    std::shared_ptr<B> ptr;
};

class B {
public:
    B() {}
    ~B() {
        std::cout << __func__ << std::endl;
    }
    std::shared_ptr<A> ptr;
};

int main(int argc, char *argv[]) {

    // std::shared_ptr<A> ptr_A = std::make_shared<A>();
    // std::shared_ptr<B> ptr_B = std::make_shared<B>();

    return 0;
}