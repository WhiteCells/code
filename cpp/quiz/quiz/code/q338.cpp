#include <iostream>
#include <string>
#include <type_traits>

template<typename T>
int f() {
    if constexpr (std::is_same_v<T, int>) {
        return 0;
    } else {
        return std::string {};
    }
}

int main() {
    std::cout << f<int>();
}