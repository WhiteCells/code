#include <iostream>

template<typename T>
void fun(T a) { std::cout << a << std::endl; }

void fun2(int a) {}

int main(int argc, char const *argv[]) {
    void(*pf)(int) = fun2;
    std::cout << &pf << std::endl;
    return 0;
}