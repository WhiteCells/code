#include <iostream>
#include <cstring>

void foo() {
    const int a = 10;
    int b = 20;
    memcpy((void *)&a, &b, sizeof(b)); // ub
    std::cout << a << std::endl;
}

int main(int argc, char *argv[]) {
    const int a = 10;
    int *p = const_cast<int *>(&a); // ub
    *p = 20;
    std::cout << a << std::endl;

    // int b = 10;
    // int *p_b = &b;
    // *p_b = 20;
    // std::cout << *p_b << std::endl;

    foo();
    return 0;
}