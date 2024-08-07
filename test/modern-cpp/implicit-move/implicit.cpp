#include <iostream>

struct X {
    X() = default;
    X(const X &) {
        std::cout << "X(const X &)" << std::endl;
    }
    // X(X &&) {
    //     std::cout << "move" << std::endl;
    // }
};

X f1(X x) {
    return x;
}

X f2() {
    X x;
    return x;
}

X f3(X &&x) {
    return x;
}

int main(int argc, char *argv[]) {
    X x1 = f1(X());
    // X x2 = f2();

    // X x3 = f3(X());
    return 0;
}