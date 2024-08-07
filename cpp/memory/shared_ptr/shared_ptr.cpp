#include <memory>
#include <iostream>

class A {
public:
    A() { std::cout << __func__ << std::endl; }
    ~A() { std::cout << __func__ << std::endl; }
};

void test_Init() {
    // recommended
    std::shared_ptr<A> ptr1 = std::make_shared<A>();

    // not recommended
    A *ptr_A = new A();
    std::shared_ptr<A> ptr2 = std::shared_ptr<A>(ptr_A);
    ptr_A = nullptr; // essential, prevent dangling pointers and double release, clarify ownership
}

// use_count()
void use_count_Example() {
    std::shared_ptr<A> ptr1 = std::make_shared<A>();

    std::cout << "shared_ptr ptr1 use count: "
        << ptr1.use_count() << std::endl;

    {
        std::shared_ptr<A> ptr2 = ptr1;
        std::cout << "shared_ptr ptr1 use count: "
            << ptr1.use_count() << std::endl;
        std::cout << "shared_ptr ptr2 use count: "
            << ptr2.use_count() << std::endl;
    }

    std::cout << "shared_ptr ptr1 use count: "
        << ptr1.use_count() << std::endl;

    std::cout << "---" << std::endl;
}

int main(int argc, char *argv[]) {
    use_count_Example();
    std::cout << "###" << std::endl;
    return 0;
}