#include <iostream>
#include <initializer_list>

class C {
public:
    C() = default;
    C(const C&) {
        std::cout << 1;
    }
};

void f(std::initializer_list<C> i) {}

int main() {
    C c{};
    std::initializer_list<C> i{ c };
    // initializer_list 可以用来初始化

    f(i);
    f(i);
    return 0;
}