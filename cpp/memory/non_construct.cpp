#include <iostream>
#include <memory>

struct A {
    A() = delete;
    int x;
};

int main(int argc, char *argv[]) {
    std::unique_ptr<A> uptr = std::make_unique<A>();
    return 0;
}