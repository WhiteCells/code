#include <iostream>
#include <vector>
#include <memory>

int main(int argc, char *argv[]) {
    std::vector<std::unique_ptr<int>> v;
    v.emplace_back(std::make_unique<int>(101));
    std::unique_ptr<int> f = std::move(v.front());
    // std::unique_ptr<int> &f = v.front();

    // v 中的智能指针还在，但其管理的内存已经交给的 l
    // std::unique_ptr<int> &f2 = v.front();
    // std::cout << "f2 value: " << *f2.get() << std::endl; // error
    while (!v.empty()) {
        std::cout << "not empty" << std::endl;
        std::cout << *v.front() << std::endl; // error
        v.pop_back();
    }
    return 0;
}