#include <memory>
#include <functional>
#include <iostream>

class Test :
    public std::enable_shared_from_this<Test> {
public:
    using callback = std::function<void()>;
    void test() {
        std::shared_ptr<Test> self = shared_from_this();
        std::cout << "self use_count: " << self.use_count() << std::endl;
        auto foo = [self]() {
        // auto foo = [&self]() {
            std::cout << "foo self use_count: " << self.use_count() << std::endl;
        };
        foo(); // foo 对象存在，则按值捕获的智能指针的引用计数不会减少，知道 foo 对象销毁，捕获的引用计数减少
        std::cout << "self use_count: " << self.use_count() << std::endl;
    }
};

class A;
void foo(std::shared_ptr<A> a_ptr);

class A :
    public std::enable_shared_from_this<A> {
public:
    A() {
        // foo(std::shared_ptr<A>(this)); // double free
        // foo(std::shared_ptr<A>(this)); 

        // foo(std::make_shared<A>(this));
        // foo(std::make_shared<A>(this));

        foo(shared_from_this());
    }
};

void foo(std::shared_ptr<A> a_ptr) {
    std::cout << "a_ptr use_count" << a_ptr.use_count() << std::endl;
}

int main(int argc, char *argv[]) {
    {
        std::shared_ptr<Test> test = std::make_shared<Test>();
        std::cout << "test use_count: " << test.use_count() << std::endl;
        test->test();
        std::cout << "test use_count: " << test.use_count() << std::endl;
    }

    A a;
    return 0;
}