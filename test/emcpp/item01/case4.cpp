#include <iostream>

const char name[] = "J. P. Briggs";
const char *ptr_name = name;

template<typename T>
void f(T param) {
}

template<typename T, size_t N>
constexpr size_t ArraySize(T(&)[N]) noexcept {
    return N;
}
int arr1[10];

int arr2[ArraySize(arr1)];

int main() {
    std::cout << ArraySize(name) << std::endl;
    std::cout << ArraySize(arr2) << std::endl;
    return 0;
}