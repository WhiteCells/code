#include <iostream>
#include <limits>

int main() {
    // std::numeric_limits<type>::digits 用于值表示的使用位数
    std::cout << std::numeric_limits<unsigned char>::digits << std::endl;
    std::cout << std::numeric_limits<short>::digits << std::endl;
    std::cout << std::numeric_limits<int>::digits << std::endl;
    std::cout << std::numeric_limits<unsigned int>::digits << std::endl;
    std::cout << std::numeric_limits<double>::digits << std::endl;
}