#include <iostream>
#include <type_traits>

int main() {
    std::cout << std::is_same<
        void(int),
        void(const int)>::value; // 1

    std::cout << std::is_same<
        void(int*),
        void(const int*)>::value; // 0
}