#include <iostream>
#include <type_traits>

int main() {
    std::cout << std::is_signed<char>::value << std::endl; // ?
    std::cout << std::is_signed<unsigned char>::value << std::endl;
    std::cout << std::is_unsigned<char>::value << std::endl;
    std::cout << std::is_unsigned<unsigned char>::value << std::endl;

    std::cout << std::is_same<char, signed char>::value << std::endl;
    std::cout << std::is_same<char, unsigned char>::value << std::endl;
    std::cout << std::is_same<signed char, unsigned char>::value << std::endl;
}

// int main() {
//     if (std::is_signed<char>::value) {
//         std::cout << std::is_same<char, signed char>::value << std::endl;
//     } else {
//         std::cout << std::is_same<char, unsigned char>::value << std::endl;
//     }
//     return 0;
// }