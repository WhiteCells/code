#include <memory>
#include <iostream>

class A {
public:
    A() { std::cout << __func__ << std::endl; }
    ~A() { std::cout << __func__ << std::endl; }
    void foo() { std::cout << __func__ << std::endl; }
};

// weak_ptr 不增加对象引用计数
void use_count_Example() {
    std::shared_ptr<A> ptr1 = std::make_shared<A>();
    std::cout << "shared_ptr ptr1 use count: "
        << ptr1.use_count() << std::endl;

    {
        std::weak_ptr<A> ptr2 = ptr1;
        std::weak_ptr<A> ptr3 = ptr1;
        std::cout << "shared_ptr ptr1 use count: "
            << ptr1.use_count() << std::endl;
        std::cout << "weak_ptr ptr2 use count: "
            << ptr2.use_count() << std::endl;
        std::cout << "weak_ptr ptr3 use count: "
            << ptr3.use_count() << std::endl;
    }

    std::cout << "---" << std::endl;
}

// weak_ptr 方法 expired() 检查 weak_ptr 所指向的对象是否不存在（过期）
void expired_Example() {
    std::weak_ptr<A> ptr;

    {
        std::shared_ptr<A> ptr_A = std::make_shared<A>();
        ptr = ptr_A;

        if (!ptr.expired()) {
            ptr.lock()->foo();
        } else {
            std::cout << "object is already destroyed" << std::endl;
        }

        std::cout << "---" << std::endl;
    }

    if (!ptr.expired()) {
        ptr.lock()->foo();
    } else {
        std::cout << "object is already destroyed" << std::endl;
    }
}

// weak_ptr 方法 lock() 将 weak_ptr 临时转换为 shared_ptr
// 会检查 weak_ptr 所指向的对象是否不存在
void lock_Example() {
    std::weak_ptr<A> ptr;

    {
        std::shared_ptr<A> ptr_A = std::make_shared<A>();
        ptr = ptr_A;

        std::shared_ptr<A> locked_ptr = ptr.lock();
        if (locked_ptr) {
            locked_ptr->foo();
        } else {
            std::cout << "object is already destroyed" << std::endl;
        }
    }

    std::shared_ptr<A> locked_ptr = ptr.lock();
    if (locked_ptr) {
        locked_ptr->foo();
    } else {
        std::cout << "object is already destroyed" << std::endl;
    }
}

int main(int argc, char *argv[]) {
    use_count_Example();
    std::cout << "###" << std::endl;
    
    expired_Example();
    std::cout << "###" << std::endl;
    
    lock_Example();
    return 0;
}