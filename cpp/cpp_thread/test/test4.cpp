#include <iostream>
#include <functional>

void foo(int &i) {
    std::cout << "foo" << std::endl;
}

int main(int argc, char *argv[]) {
    int i = 1;
    int &ri = i;
    auto f = std::bind(foo, std::move(ri));
    f();
    return 0;
}