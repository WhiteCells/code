#include <iostream>

template<typename T>
void f(T param) {
    // param[0] = 'w';    // error
    // param = nullptr; 
}

int main(int args, char **argv) {
    // int x = 27;
    // const int cx = x;
    // const int &rx = cx;

    // f(x);
    // f(cx);
    // f(rx); 
    // f(27);

    // int a = 10;
    // int &b = a;
    // f(b);
    // b = 20;
    // std::cout << a << std::endl;

    const char *const ptr = "h";
    f(ptr);
    return 0;
}