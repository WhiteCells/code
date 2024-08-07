#include <iostream>

class C {
public:
    auto foo() -> int;
};

int C::foo() {
    std::cout << __func__ << std::endl;
    return 1;
}

int main(int argc, char *argv[]) {
    C c;
    c.foo();
    return 0;
}