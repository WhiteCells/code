#include <iostream>
#include <type_traits>

// 通用版本，用于不匹配特定签名的情况
template <typename T>
void f(T &t, ...)
{
    std::cout << "except" << std::endl;
}

// 匹配 T::f(int, double) 的模板函数
template <typename T, typename = std::enable_if_t<std::is_same_v<decltype(std::declval<T>().f(int {}, double {})), void>>>
void f(T &t, int a, double b)
{
    t.f(a, b);
}

// 匹配 T::f(int, double, int) 的模板函数
template <typename T, typename = std::enable_if_t<std::is_same_v<decltype(std::declval<T>().f(int {}, double {}, int {})), void>>>
void f(T &t, int a, double b, int c)
{
    t.f(a, b, c);
}

struct A
{
    void f(int a, double) { std::cout << "a: f(int, double)" << std::endl; }
    void f(int a, double, int) { std::cout << "a: f(int, double, int)" << std::endl; }
};

int main(int argc, char *argv[])
{
    A a;
    f(a, 1);         // 调用通用版本，输出 "except"
    f(a, 1, 2.0);    // 调用 f(int, double)
    f(a, 1, 2.0, 3); // 调用 f(int, double, int)
    return 0;
}