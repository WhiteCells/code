#include <iostream>

struct A
{
    void foo(int a) const { std::cout << "v1" << std::endl; }
    void foo(int a, int b) const { std::cout << "v2" << std::endl; }
};

template <typename T, typename Enable>
struct f_impl
{
    static void f(T &, int a) { std::cout << "foo(int a)" << std::endl; }
    static void f(T &, int a, int b) { std::cout << "foo(int a, int b)" << std::endl; }
};

template <typename T>
struct f_impl<T, std::void_t<decltype(std::declval<T>().f(int {}, int {}))>>
{
    static void f(T &t, int a, int b) { t.f(a, b); };
};

template <typename ...Types>
using int1 = int64_t;

template <typename T>
struct f_impl<T, ::int1<decltype(std::declval<T>().f(int {}))>>
{
    static void f(T &t, int a) { t.f(a); };
};

template <typename T>
void f(T &t, int a)
{
    return f_impl<T, void>::f(t, a);
}

template <typename T>
void f(T &t, int a, int b)
{
    return f_impl<T, int>::f(t, a, b);
}

int main(int argc, char *argv[])
{
    A a;
    f(a, 1);
    f(a, 1, 2);
    return 0;
}
