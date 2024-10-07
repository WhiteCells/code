#include <iostream>
#include <cstddef> // for size_t

int main() {
    unsigned int u = -1;
    size_t s = -1;

    std::cout << "unsigned int u = -1; u = " << u << std::endl;
    std::cout << "size_t s = -1; s = " << s << std::endl;

    int a = -1;
    (unsigned)a;
    std::cout << a << std::endl;

    return 0;
}
