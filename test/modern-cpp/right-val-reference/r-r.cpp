#include <iostream>

class X {
public:
    X() { std::cout << "X()" << std::endl; }
    X(const X &) { std::cout << "X(const X &)" << std::endl; }
    ~X() { std::cout << "~X()" << std::endl; }
};

X makeX() {
    X x1;
    return x1;
}

int main(int argc, char const *argv[]) {
    X &&x2 = makeX();
    // X x2 = makeX();
    return 0;
}