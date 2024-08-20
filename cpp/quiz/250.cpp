#include <iostream>

template<typename T>
void foo(T ...) {
    std::cout << "a" << std::endl;
}

template<typename... T>
void foo(T ...) {
    std::cout << "b" << std::endl;
}

int main(int argc, char *argv[]) {
    foo(1);
    foo(1, 2);
    return 0;
}