#include <iostream>

template<class T>
void f(T) {
    static int i = 0;
    std::cout << ++i;
}

int main() {
    f(1);
    f(1.1);
    f(1);
}