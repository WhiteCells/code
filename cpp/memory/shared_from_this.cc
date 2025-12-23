#include <memory>
#include <iostream>

class A : public std::enable_shared_from_this<A>
{
public:
    std::shared_ptr<A> get_shared()
    {
        return shared_from_this();
    }

    std::weak_ptr<A> get_weak()
    {
        return weak_from_this();
    }
};

int main(int argc, char *argv[])
{
    // auto a = A();
    // auto a_shared = a.get_shared(); // This will cause undefined behavior since 'a' is not managed by a shared_ptr

    auto a = std::make_shared<A>();
    auto a_weak = a->get_weak();
    if (a_weak.lock()) {
        auto a_shared = a_weak.lock();
        std::cout << "a_shared use_count: " << a_shared.use_count() << std::endl;
    }
    else {
        std::cout << "a_weak is expired." << std::endl;
    }
    std::cout << "a use_count: " << a.use_count() << std::endl; // 1
    return 0;
}