#include <iostream>
#include <cassert>

void foo1() {
    int x1 = 0;
    decltype(x1) x2 = 0;
    std::cout << typeid(x2).name() << std::endl;

    double x3 = 1.1;
    decltype(x1 + x3) x4 = x1 + x3;
    std::cout << typeid(x4).name() << std::endl;
}

// 非静态成员变量中使用
struct A {
    int a;
    decltype(a) b;
    double c;
    decltype(a + c) d;
};

// C++14
template<class T1, class T2>
auto sum(T1 a, T2 b) {
    return a + b;
}

void foo2() {
    auto r = sum(1, 1.1);
    std::cout << r << std::endl;
}

// decltype 与 auto 搭配使用
template<class T1, class T2>
auto sum2(T1 a, T2 b) -> decltype(a + b) {
    return a + b;
}

void foo3() {
    auto r = sum(1, 1.1);
    std::cout << r << std::endl;
}

// auto 作为返回类型占位符的问题
template<class T>
// auto returnRef(T &t) { // compilation failed
auto returnRef(T &t) -> decltype(t) {
    return t;
}

void foo4() {
    int x = 1;
    static_assert(
        std::is_reference_v<decltype(returnRef(x))> // C++17
        // std::is_reference<decltype(returnRef(x))>::value // C++11
        );
}

// 如果 e 是一个函数或仿函数，则 decltype(e) 是函数或仿函数的返回值类型
void foo5() {
    int x = 1;
    auto &r = returnRef(x);
    static_assert(
        std::is_same_v<decltype(returnRef(x)), decltype(r)>
        );
}

// 如果 e 是一个类型为 T 的左值，则 decltype(e) 是 T &
void foo6() {
    int x = 1;
    int &rx = x;
    // decltype(rx) r = 1; compilation failed
    int y = 2;
    decltype(rx) ry = y;
}

// 如果 e 是一类型为 T 的将亡值，则 decltype(e) 是 T &&
void foo7() {
    int x = 1;
    decltype(std::move(x)) y = std::move(x);
    static_assert(
        std::is_same_v<decltype(y), int &&>
        );
}

// 如果 e 是一个类型为 T 的长度为 L 的数组类型，则 decltype(e) 是 T [L]
void foo8() {
    int arr[] {1, 2, 3};
    decltype(arr) arr2 {1, 2, 3};
    // decltype(arr) arr3 {1, 2, 3, 4}; // compilation failed
    static_assert(std::is_same_v<decltype(arr), int[3]>
                  );
}

class AA {};

void foo9() {
    decltype(AA()) a;
    std::cout << typeid(a).name() << std::endl;
}

// complex example
void foo10() {
    int i;
    int *j;
    int n[10];
    decltype(i = 0) a = i; // int &
    decltype(0, i) b = i; // int &
    decltype(i, 0) c = i; // int
    decltype(n[5]) d = i; // int &
    decltype(*j) e = i; // int &
    decltype(static_cast<int &&>(i)) f = 0; // int &&
    decltype(i++) g = i; // int
    decltype(++i) h = i; // int &
    decltype("hello") k = "world"; // const char (&)[6]
}

int main(int argc, char const *argv[]) {
    // foo1();
    // foo2();
    // foo3();
    // foo4();
    // foo5();
    // foo6();
    // foo7();
    // foo8();
    foo9();

    std::cout << std::boolalpha << true << std::endl;

    // const int &&foo11();
    // decltype(foo11); // decltype(foo)推导类型为int const
    return 0;
}