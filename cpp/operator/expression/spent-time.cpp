#include <iostream>
#include <chrono>

void spendTime(auto f) {
    auto start = std::chrono::high_resolution_clock::now();
    f();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << duration.count() << "ms\n";
}

void foo() {
    size_t k = 0;
    // for (size_t i = 0; i < (size_t)1e10; ++i) {
    for (size_t i = 0; i < 1e9; ++i) {
        ++k;
        // k++;
    }
    if (k == (int)1e10) {
        k -= 1;;
    }
    std::cout << k << std::endl;
}

int main() {
    spendTime(foo);
    return 0;
}