#include <iostream>
#include <memory>

class A
{
public:
    A()
    {
        std::cout << "A()" << std::endl;
    }
    ~A()
    {
        std::cout << "~A()" << std::endl;
    }
};

int main(int argc, char *argv[]) {
    std::shared_ptr<int> a = std::make_shared<int>(1);
    std::shared_ptr<int> b = a;
    std::shared_ptr<int> c = a;

    std::cout << a.use_count() << std::endl;
    std::cout << b.use_count() << std::endl;
    std::cout << c.use_count() << std::endl; // 3

    a = std::make_shared<int>(1);

    std::cout << a.use_count() << std::endl; // 1
    std::cout << b.use_count() << std::endl; // 2
    std::cout << c.use_count() << std::endl; // 2

    std::shared_ptr<A> d = std::make_shared<A>();
    d = std::make_shared<A>();
    std::cout << d.use_count() << std::endl;

    std::cout << "---" << std::endl;
    return 0;
}