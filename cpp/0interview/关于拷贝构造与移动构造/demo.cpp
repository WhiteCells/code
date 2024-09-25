#include <iostream>

class A
{
public:
    A()
    {
        std::cout << "A()" << std::endl;
    }
    A(A &&)
    {
        std::cout << "A(A &&)" << std::endl;
    }
    A(const A &) = delete;
    A &operator=(const A &) = delete;
    ~A()
    {
        std::cout << "~A()" << std::endl;
    }
};

void foo(A a)
{
    A a2 = std::move(a);
}

// 右值引用只能传递右值
void foo2(A &&a)
{
    A a2 = std::move(a);
}

int main(int argc, char *argv[])
{
    A a;
    foo(A());
    // 传递右值引用，std::move() 在存在移动构造时就不会调用拷贝构造
    foo(std::move(a));

    foo2(std::move(a)); // a 的资源已经转移

    A a2;
    foo2(std::move(a2)); // OK
    foo2(A());           // OK
    return 0;
}