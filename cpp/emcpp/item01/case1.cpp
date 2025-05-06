#include <iostream>
#include <typeinfo>

template<typename T>
void f(T &param) {}

int main() {
    int x = 27;
    const int cx = x;
    const int &rx = cx;

    f(x);
    f(cx);
    f(rx);

    return 0;
}