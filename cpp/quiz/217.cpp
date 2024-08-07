#include <iostream>

int main() {
    int i = 1;
    int const& a = i > 0 ? i : 1;
    // const int& a = i;
    // int& const a = i;
    i = 2;
    std::cout << i << a; // 21
    return 0;
}