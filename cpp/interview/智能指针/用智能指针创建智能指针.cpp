#include <iostream>
#include <memory>

class A {
public:
    A() { std::cout << __func__ << std::endl; }
    ~A() { std::cout << __func__ << std::endl; }
};

class B {
public:
    B(std::shared_ptr<A> ptr) : a_ptr(ptr) {
        std::cout << "ptr use count: " << ptr.use_count() << std::endl;
        std::cout << __func__ << std::endl;
    }
    ~B() {
        std::cout << __func__ << std::endl;
    }

private:
    std::shared_ptr<A> a_ptr;
};

void foo(std::shared_ptr<B> ptr) {
    auto b_ptr = ptr;
}

int main(int argc, char *argv[]) {
    std::shared_ptr<A> a1_ptr = std::make_shared<A>();
    std::shared_ptr<B> b1_ptr = std::make_shared<B>(a1_ptr);

    // 如果 foo 是一个异步函数，而 foo 内部持有 b1_ptr 或者 a_ptr 的引用，
    // 那么在 foo 未完成时，主线程继续执行并可能导致 a1_ptr 重新指向一个新的 A 对象。
    // 当 a1_ptr 重新分配时，原先指向的 A 对象的引用计数会减少。
    // 如果此时 foo 还在运行并且持有 b1_ptr，
    // 那么原先被 a1_ptr 指向的 A 对象的生命周期是由 B 中的 a_ptr 管理的。
    // 因为 b1_ptr 和 a1_ptr 的生命周期是分开的，
    // 所以即使 a1_ptr 被重新分配，只要 b1_ptr 仍然存在，原先的 A 对象的生命周期仍然是安全的。
    foo(b1_ptr);
    std::cout << "ptr use count: " << a1_ptr.use_count() << std::endl;

    // a1_ptr 原先的管理的内存由 A::a_ptr 管理
    a1_ptr = std::make_shared<A>();
    std::cout << "ptr use count: " << a1_ptr.use_count() << std::endl;

    return 0;
}