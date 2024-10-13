#include <iostream>

template <typename T1, typename T2, typename RT = decltype(T1 {} + T2 {})>
RT add(const T1 &a, const T2 &b)
{
    return a + b;
}

template <typename T1, typename T2>
auto add_11(const T1 &a, const T2 &b) -> decltype(a + b)
{
    return a + b;
}

decltype(auto) add_20(const auto &a, const auto &b)
{
    return a + b;
}

int main(int argc, char *argv[])
{
    std::cout << typeid(add(2147483648, 1)).name() << std::endl;
    std::cout << typeid(add_11(2147483648, 1)).name() << std::endl;
    std::cout << typeid(add_20(2147483648, 1)).name() << std::endl;
    
    return 0;
}