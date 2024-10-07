#include <iostream>

template<typename T>
void foo(T &x) {
    std::cout << std::is_same_v<const int, T>;
}

template<typename T>
void bar(const T &x) {
    std::cout << std::is_same_v<const int, T>;
}

int main() {
    const int i {};
    int j {};

    foo(i); // 1
    foo(j); // 0
    bar(i); // 0
    bar(j); // 0
}