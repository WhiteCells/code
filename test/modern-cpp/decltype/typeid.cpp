#include <iostream>
#include <typeinfo>
#include <wchar.h>
#include <type_traits>

int main(int argc, char const *argv[]) {
#if 1
    int a = 10;
    const int a2 = 10;
    float b = 1.1F;
    double b2 = 1.1;

    std::cout << typeid(a).name()  << std::endl;
    std::cout << typeid(11.1).name() << std::endl;
    std::cout << typeid(a2).name() << std::endl;
    std::cout << typeid(b).name()  << std::endl;
    std::cout << typeid(b2).name() << std::endl;

    std::cout << typeid(b + b2).name() << std::endl;
    class A {};
    std::cout << typeid(A).name() << std::endl;

    // auto t1 = typeid(int);
    auto &t2 = typeid(int);
    auto *t3 = &typeid(int);

    const std::type_info &t22 = typeid(1);
    const std::type_info *t33 = &typeid(1);

    std::cout << "--" << std::is_same<decltype(t22), decltype(t33)>::value << std::endl;
    std::cout << "--" << std::is_same<decltype(a), decltype(1)>::value << std::endl;

    const int x = 1;
    int y = 1;
    std::cout << (typeid(x).name() == typeid(y).name()) << std::endl;

#endif

// #define test
#ifdef test
    unsigned a = 10; // 无符号整型
    // unsigned int a = 10;
    // 10 是字面量，默认为 int 类型
    // C++ 提供字面量后缀 U 来修饰无符号整型
    unsigned a2 = 10U;
    // 一般情况不写字面量后缀不会有很大的问题

    int b = 10; // 有符号整型
    // signed int b = 10;
    // 默认就是有符号的，所有没有提供相应的字面量后主

    long c = 10; // 长整型
    // signed long int c = 10;
    // C++ 提供字面量后缀 L 来修饰长整型
    long c2 = 10L;

    long long d = 10; // 长长整型
    // signed long long int d = 10;
    // C++ 提供字面量后缀 LL 来修饰长长整型
    long long d2 = 10LL;

    unsigned long long e = 10; // 无符号长长整型
    // unsigned long long int e = 10;
    // C++ 提供字面量后缀 ULL 来修饰无符号长长整型
    unsigned long long e2 = 10ULL;
    // printf 占位符
    printf("%llu", e2);
    // printf("%ull", e2);

    float f = 1.1; // 单精度浮点类型
    // 1.1 字面量默认为双精度浮点类型
    // C++ 提供字面量后缀 F 来显式声明单精度浮点类型
    float f2 = 1.1F;

    double g = 1.1; // 双精度浮点类型

    // UTF-8
    char c = u8'1';

    // UTF-16
    char c2 = u'1';
    
    // UTF-32
    char c3 = U'1';

    // wchar_t
    wchar_t c4 = L'字';

    // wchar_t
    const wchar_t *st = L"你好";
#endif
    return 0;
}