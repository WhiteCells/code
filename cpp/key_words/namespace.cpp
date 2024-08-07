#include <iostream>

namespace ns {
    int a = 10;
}

namespace ns {
    int b = 40;
}

int a = 20;

int main() {
    std::cout << a << '\n';
    std::cout << ns::a << '\n';
    int a = 30;
    std::cout << a << '\n';
    std::cout << ::a << '\n';
    std::cout << ns::b << '\n';
    return 0;
}

