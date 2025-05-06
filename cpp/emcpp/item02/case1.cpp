#include <iostream>

void someFunc(int, double) {
    std::cout << "someFunc" << std::endl;
}

void foo(int, double) {
    std::cout << "foo" << std::endl;
}

template<typename T>
void foo2(T &&param) {
    std::cout << typeid(param).name() << std::endl;
}

int main() {
    auto func1  = someFunc;
    auto &func2 = someFunc;
    // func1(1, 2);
    // func2 = foo;
    auto func3 = foo;
    // func2 = func3;
    func1 = func3;

    // foo2({ 1, 2 });
    foo2(std::pair<int, int>(1, 2));

    return 0;
}