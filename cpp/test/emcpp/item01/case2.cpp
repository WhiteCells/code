#include <iostream>

template<typename T>
void f(T &&param) {}

template<typename T>
auto max(T &&a, T &&b) {
    return a > b ? a : b;
}

int main(int args, char **argv) {
    int x = 27;
    const int cx = x;
    const int &rx = cx;

    f(x);  // x 是左值, 所以 T 是 int &
           // param 类型也是 int &

    f(cx); // cx 是左值, 所以 T 是 const int &
           // param 类型也是 const int &

    f(rx); // rx 是左值, 所以 T 是 const int &
           // param 类型也是 const int & 

    f(27); // 27 是右值, 所以 T 是 int
           // param 类型是 int &&

    auto a = max(1, 2);
    std::cout << a << std::endl;
    auto b = max(-1, -2);
    std::cout << b << std::endl;
    auto c = max(a, b);
    std::cout << c << std::endl;

    auto &d = c;
    auto &e = d;
    return 0;
}