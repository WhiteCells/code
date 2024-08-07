#include <iostream>

#include <utility>

void Exchange() {
    int a = 10;
    int b = 20;
    int* pa = &a;
    int* pb = &b;

    // int* old_pa = pa;
    // pa = pb;
    int* old_pa = std::exchange(pa, pb);

    std::cout << *pa << '\n';
    std::cout << *pb << '\n';
    std::cout << *old_pa << '\n';
}

int main() {
    Exchange();
    return 0;
}
