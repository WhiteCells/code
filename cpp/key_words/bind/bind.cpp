#include <iostream>
#include <functional>

using Func = std::function<void()>;

void foo(const Func &f) {
    f();
}

int main(int argc, char *argv[]) {
    int a = 10;
    Func func = std::bind([](int *a) { std::cout << *a << std::endl; }, &a);
    foo(func);
    return 0;
}