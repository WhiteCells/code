#include <iostream>
#include <memory>

int main(int argc, char *argv[]) {
    std::shared_ptr<int> a = std::make_shared<int>(1);
    std::shared_ptr<int> b = a;
    std::shared_ptr<int> c = a;

    std::cout << a.use_count() << std::endl;
    std::cout << b.use_count() << std::endl;
    std::cout << c.use_count() << std::endl;

    a = std::make_shared<int>(1);

    std::cout << a.use_count() << std::endl; // 1
    std::cout << b.use_count() << std::endl; // 2
    std::cout << c.use_count() << std::endl; // 2
    return 0;
}