#include <iostream>
#include <memory>
#include <functional>

class A {
public:
    A() { std::cout << "A()" << std::endl; }
    ~A() { std::cout << "~A()" << std::endl; }
};

void foo(std::shared_ptr<A> a) {
    std::cout << "a_ptr use_count: " << a.use_count() << std::endl;
}

int main(int argc, char *argv[]) {
    {
        auto a_ptr = std::make_shared<A>();
        std::cout << "a_ptr use_count: " << a_ptr.use_count() << std::endl;
        auto f = std::bind(foo, a_ptr);
        f();
        // f 和 a_ptr 对象都没有结束对内存的管理
        std::cout << "a_ptr use_count: " << a_ptr.use_count() << std::endl;
    }
    return 0;
}