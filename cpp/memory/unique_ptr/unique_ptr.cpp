#include <memory>
#include <iostream>

class A {
public:
    A() {  std::cout << __func__ << std::endl; }
    ~A() { std::cout << __func__ << std::endl; }
};

void test_Init() {
    A *ptr_A = new A();
    std::unique_ptr<A> ptr1 = std::unique_ptr<A>(ptr_A);
    std::unique_ptr<A> ptr2 = std::make_unique<A>(); // C++14

    {
        std::unique_ptr<A> ptr3 = std::move(ptr2);
    }

    std::cout << "---" << std::endl;
}

int main(int argc, char *argv[]) {
    test_Init();
    return 0;
}