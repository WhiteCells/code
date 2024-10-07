#include <iostream>
#include <cassert>

auto f = [](int &a) -> auto &{ return a; };

void foo() {
    auto x1 = 1;
    auto &x2 = f(x1);
    assert(&x1 == &x2);
}

int main() {
    foo();
    return 0;
}