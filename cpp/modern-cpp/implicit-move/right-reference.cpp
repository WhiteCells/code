#include <iostream>
#include <string>

struct X {
    X() = default;
    X(const X &) = default;
    X(X &&) {
        std::cout << "move" << std::endl;
    }
};

X f(X &&x) {
    return x;
}

void test() {
    X x;
    throw x;
}

int main(int argc, char *argv[]) {
    // X x = f(X());

    try {
        test();
    } catch (...) {
        
    }
    return 0;
}