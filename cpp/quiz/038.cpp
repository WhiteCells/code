#include <iostream>

int main()
{
    int a = 0;
    // const int a = 0;
    decltype((a)) b = a;
    // decltype(a) b = a;
    b++;
    std::cout << a << b;
}
