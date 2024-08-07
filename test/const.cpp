#include <iostream>

int main(int argc, char *argv[]) {
    const int a = 10;
    int *p = const_cast<int *>(&a);
    *p = 20;
    std::cout << a << std::endl;
    return 0;
}