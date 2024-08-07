#include <memory>
#include <iostream>

/**
 * auto_ptr C++98 中引入，C++11 中弃用
 * 
 * 弃用原因：
 * 1. auto_ptr 使用所有权移动语义，现代 C++ 更强调所有权管理和资源生命周期管理
 * 2. auto_ptr 的所有权转移是通过复制构造函数和赋值运算符实现的，这些操作在多线程环境中可能导致竞态条件和未定义行为
 * 3. C++11 中引入 unique_ptr 能更好的管理所有权
 */ 

class A {
public:
    A() {
        std::cout << __func__ << std::endl;
    }
    ~A() {
        std::cout << __func__ << std::endl;
    }
};

int main(int argc, char *argv[]) {
    std::auto_ptr<A> ptr = std::auto_ptr<A>(new A());
    {
        std::auto_ptr<A> ptr2 = ptr;
    }
    std::cout << "---" << std::endl;
    return 0;
}