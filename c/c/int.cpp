#include <iostream>
#include <cstdint>

// 64 位操作系统
void UseINT_MAX() {
    std::cout << INT_MAX   << '\n'; // 2147483647
    std::cout << INT16_MAX << '\n'; // 32767
    std::cout << INT32_MAX << '\n'; // 2147483647
    std::cout << INT64_MAX << '\n'; // 9223372036854775807
}

// 64 位操作系统
void UseINT_MIN() {
    std::cout << INT_MIN   << '\n'; // -2147483648
    std::cout << INT16_MIN << '\n'; // -32768
    std::cout << INT32_MIN << '\n'; // -2147483648
    std::cout << INT64_MIN << '\n'; // -9223372036854775808
}

// 64 位操作系统
void UseUINT() {
    std::cout << UINT_MAX   << '\n'; // 4294967295
    std::cout << UINT16_MAX << '\n'; // 65535
    std::cout << UINT32_MAX << '\n'; // 4294967295
    std::cout << UINT64_MAX << '\n'; // 18446744073709551615 size_t
}

int main() {
    UseINT_MAX();
    UseINT_MIN();
    UseUINT();
    return 0;
}