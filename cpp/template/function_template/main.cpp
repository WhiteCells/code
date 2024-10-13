#include <iostream>
#include <type_traits>

struct A
{
    A() = default;
    A(const A &) = delete;
    A &operator=(const A &) = delete;
};

template <typename T>
void foo(T &&t)
{
}

template <typename T>
void f(T &&t)
{
}

void reference()
{
    int a = 10;
    f(a); // a 是左值表达式，f 是 f<int &> 形参类型是 int &
    f<int &>(a);

    int &ra = a;
    f(ra); // ra 是左值表达式，f 是 f<int &> 形参类型是 int &
    f<int &>(ra);

    int &&rra = 1;
    f(rra); // rra 是左值表达式，f 是 f<int &> 形参类型是 int &
    f<int &>(rra);

    f(int {1}); // int {1} 是右值表达式，f 是 f<int &&> 形参类型是 int &&
    f<int &&>(int {1});

    const int ca = 10;
    f(ca);
    f<const int &>(ca);

    const int &cra = a;
    f(cra);
    f<const int &>(cra);

    const int &&crra = 10;
    f(crra);
    f<const int &>(crra);
}

template <typename T>
constexpr T &&forward(T &Arg) noexcept
{
    return static_cast<T &&>(Arg);
}

template <typename T>
constexpr void perfect_forword(T &&arg) noexcept
{
    if (std::is_lvalue_reference<decltype(arg)>::value) {
        std::cout << "is lvalue reference" << std::endl;
    }
    else if (std::is_rvalue_reference<decltype(arg)>::value) {
        std::cout << "is rvalue reference" << std::endl;
    }
}

int main(int argc, char *argv[])
{
    reference();
    
    int a = 10;
    ::forward<int>(a);    // 返回 int，   因为 T 为 int，   所以 T && 是 int&&
    ::forward<int &>(a);  // 返回 int &， 因为 T 为 int &， 所以 T && 是 int &
    ::forward<int &&>(a); // 返回 int &&，因为 T 为 int &&，所以 T && 为 int &&

    perfect_forword(a);
    perfect_forword(std::move(a));
    perfect_forword(int {1});
    return 0;
}