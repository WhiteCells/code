#include <iostream>

void someFunc(int, double) {
    std::cout << "someFunc" << std::endl;
}

template<typename T>
void f1(T param) {
    param(1, 2);
}

template<typename T>
void f2(T &param) {
    param(1, 2);
}

int main() {
    f1(someFunc);
    f2(someFunc);
    int a[10];
    void(*b)(int, double) = someFunc;

    return 0;
}
