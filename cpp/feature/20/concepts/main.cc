#include <concepts>
#include <cmath>
#include <iostream>
#include <string>

// 定义数值类型概念
template <typename T>
concept Numeric = std::integral<T> ||
                  std::floating_point<T> ||
                  std::is_same_v<T, std::string> ||
                  std::is_same_v<T, std::wstring> ||
                  std::is_same_v<T, std::basic_string<char>> ||
                  std::is_same_v<T, const char *>;

// 安全的平方根函数
template <Numeric T>
auto safe_sqrt(T value)
{
    if constexpr (std::integral<T>) {
        // 整数类型转换为double计算
        return std::sqrt(static_cast<double>(value));
    }
    else if constexpr (std::is_same_v<T, const char *>) {
        return -1;
    }
    else {
        // 浮点类型直接计算
        return std::sqrt(value);
    }
}

template <typename T>
auto safe_sqrt2(T value)
{
    if constexpr (std::integral<T>) {
        // 整数类型转换为double计算
        return std::sqrt(static_cast<double>(value));
    }
    else {
        // 浮点类型直接计算
        return std::sqrt(value);
    }
}

/**

~/dev/cpp-project/code » g++ test3.cc -std=c++20         cells@pc
test3.cc: In instantiation of ‘auto safe_sqrt2(T) [with T = const char*]’:
test3.cc:46:15:   required from here
   46 |     safe_sqrt2("hello");
      |     ~~~~~~~~~~^~~~~~~~~
test3.cc:32:25: 错误：对‘sqrt(const char*&)’的调用没有匹配的函数
   32 |         return std::sqrt(value);
      |                ~~~~~~~~~^~~~~~~
test3.cc:32:25: 附注：there are 4 candidates
包含于文件 test3.cc:2:
/usr/include/c++/15.2.1/cmath:461:5: 附注：备选 1: ‘template<class _Tp> constexpr typename __gnu_cxx::__enable_if<std::__is_integer<_Tp>::__value, double>::__type std::sqrt(_Tp)’
  461 |     sqrt(_Tp __x)
      |     ^~~~
/usr/include/c++/15.2.1/cmath:461:5: 附注：template argument deduction/substitution failed:
/usr/include/c++/15.2.1/cmath: In substitution of ‘template<class _Tp> constexpr typename __gnu_cxx::__enable_if<std::__is_integer<_Tp>::__value, double>::__type std::sqrt(_Tp) [with _Tp = const char*]’:
test3.cc:32:25:   required from ‘auto safe_sqrt2(T) [with T = const char*]’
   32 |         return std::sqrt(value);
      |                ~~~~~~~~~^~~~~~~
test3.cc:46:15:   required from here
   46 |     safe_sqrt2("hello");
      |     ~~~~~~~~~~^~~~~~~~~
/usr/include/c++/15.2.1/cmath:461:5: 错误：no type named ‘__type’ in ‘struct __gnu_cxx::__enable_if<false, double>’
  461 |     sqrt(_Tp __x)
      |     ^~~~
包含于文件 /usr/include/features.h:524,
        于 /usr/include/c++/15.2.1/x86_64-pc-linux-gnu/bits/os_defines.h:39,
        于 /usr/include/c++/15.2.1/x86_64-pc-linux-gnu/bits/c++config.h:727,
        于 /usr/include/c++/15.2.1/bits/version.h:51,
        于 /usr/include/c++/15.2.1/concepts:38,
        于 test3.cc:1:
test3.cc: In instantiation of ‘auto safe_sqrt2(T) [with T = const char*]’:
test3.cc:46:15:   required from here
   46 |     safe_sqrt2("hello");
      |     ~~~~~~~~~~^~~~~~~~~
/usr/include/bits/mathcalls.h:180:1: 附注：备选 2: ‘double sqrt(double)’
  180 | __MATHCALL (sqrt,, (_Mdouble_ __x));
      | ^~~~~~~~~~
包含于文件 /usr/include/math.h:275,
        于 /usr/include/c++/15.2.1/cmath:55:
/usr/include/bits/mathcalls.h:180:1: 附注：no known conversion for argument 1 from ‘const char*’ to ‘double’
  180 | __MATHCALL (sqrt,, (_Mdouble_ __x));
      | ^
/usr/include/c++/15.2.1/cmath:449:3: 附注：candidate 3: ‘constexpr float std::sqrt(float)’
  449 |   sqrt(float __x)
      |   ^~~~
/usr/include/c++/15.2.1/cmath:449:14: 附注：no known conversion for argument 1 from ‘const char*’ to ‘float’
  449 |   sqrt(float __x)
      |        ~~~~~~^~~
/usr/include/c++/15.2.1/cmath:453:3: 附注：candidate 4: ‘constexpr long double std::sqrt(long double)’
  453 |   sqrt(long double __x)
      |   ^~~~
/usr/include/c++/15.2.1/cmath:453:20: 附注：no known conversion for argument 1 from ‘const char*’ to ‘long double’
  453 |   sqrt(long double __x)
      |        ~~~~~~~~~~~~^~~
*/

/**
~/dev/cpp-project/code » g++ test3.cc -std=c++20     1 ↵ cells@pc
test3.cc: In function ‘int main()’:
test3.cc:105:14: 错误：对‘safe_sqrt(const char [6])’的调用没有匹配的函数
  105 |     safe_sqrt("hello");
      |     ~~~~~~~~~^~~~~~~~~
test3.cc:105:14: 附注：there is 1 candidate
test3.cc:11:6: 附注：备选 1: ‘template<class T>  requires  Numeric<T> auto safe_sqrt(T)’
   11 | auto safe_sqrt(T value)
      |      ^~~~~~~~~
test3.cc:11:6: 附注：template argument deduction/substitution failed:
test3.cc:11:6: 附注：constraints not satisfied
test3.cc: In substitution of ‘template<class T>  requires  Numeric<T> auto safe_sqrt(T) [with T = const char*]’:
test3.cc:105:14:   required from here
  105 |     safe_sqrt("hello");
      |     ~~~~~~~~~^~~~~~~~~
test3.cc:7:9:   required for the satisfaction of ‘Numeric<T>’ [with T = const char*]
test3.cc:7:36: 附注：no operand of the disjunction is satisfied
    7 | concept Numeric = std::integral<T> || std::floating_point<T>;
      |                   ~~~~~~~~~~~~~~~~~^~~~~~~~~~~~~~~~~~~~~~~~~
cc1plus: 附注：set ‘-fconcepts-diagnostics-depth=’ to at least 2 for more detail
*/
int main()
{

    static_assert(Numeric<int>);
    static_assert(Numeric<double>);
    static_assert(Numeric<std::string>);
    // 使用示例
    safe_sqrt(9.0);
    // OK
    auto res = safe_sqrt(16);
    std::cout << typeid(res).name() << std::endl;
    std::cout << res << std::endl;
    // OK，自动转换为double
    safe_sqrt("hello");
    // safe_sqrt2("hello");
    // 编译错误：不满足Numeric概念
}
