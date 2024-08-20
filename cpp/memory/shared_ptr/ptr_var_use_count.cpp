#include <memory>
#include <iostream>

class A {
public:
    A() {
        data_ = new char[10] {};
    }
    ~A() {
        std::cout << "~A()" << std::endl;
        delete[] data_;
    }
    char *data_;
};

std::shared_ptr<A> a_ptr = std::make_shared<A>();

void foo(char *data) {
    std::cout << "foo(char *) a_ptr use count: " << a_ptr.use_count() << std::endl;
}

// void foo(std::shared_ptr<A> ptr) {
//     std::cout << "foo(std::shared_ptr<A>) a_ptr use count: " << a_ptr.use_count() << std::endl;
// }

// 不增加引用计数
void foo(const std::shared_ptr<A> &ptr) {
    std::cout << "foo(std::shared_ptr<A>) a_ptr use count: " << a_ptr.use_count() << std::endl;
}

void test_1() {
    a_ptr = std::make_shared<A>();
    std::cout << "a_ptr use_count: " <<  a_ptr.use_count() << std::endl;
    foo(a_ptr->data_);
    foo(a_ptr);
    std::cout << "a_ptr use_count: " << a_ptr.use_count() << std::endl;
}

class B {
public:
    B() {
        a = std::make_shared<A>();
    }

    void foo() {
        std::cout << "--- (foo)" << std::endl;
        a = std::make_shared<A>();
        std::cout << "--- (foo)" << std::endl;
        std::cout << a.use_count() << std::endl;
    }
    
    std::shared_ptr<A> a;
};

void test_2() {
    B b;
    b.foo();
    std::cout << "---" << std::endl;
}

int main(int argc, char *argv[]) {
    // test_1();
    test_2();
    return 0;
}