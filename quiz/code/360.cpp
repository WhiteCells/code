#include <iostream>
#include <type_traits>

int main() {
    std::cout << std::is_const_v<const int *>;
    std::cout << std::is_const_v<int *const>;

    std::cout << std::is_const_v<const int[1]>;
    std::cout << std::is_const_v<const int **>;
    std::cout << std::is_const_v<int *const *>;
    std::cout << std::is_const_v<int const **>;

    std::cout << std::is_const_v<const int(*)[1]>;
    std::cout << std::is_const_v<const int *[1]>;
    std::cout << std::is_const_v<int *const [1]>;
    std::cout << std::is_const_v<const int[1][1]>;
}