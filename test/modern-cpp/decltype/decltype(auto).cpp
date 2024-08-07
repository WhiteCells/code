#include <iostream>

void foo1() {
    decltype(auto) i = 1;
    decltype(auto) ri = (i);
    // int test();
    // decltype(auto) i2;
    // decltype(auto) i3 = {1, 2}; // compilation failed {1, 2} not an expression

    const int a = 1;
    decltype(auto) b = a; // const int b = a;
    decltype(auto) ra = (a); // const int &ra = a;
}

// decltype(auto) 作为函数返回值
template<class T>
decltype(auto) returnRef(T &t) { // C++14
    return t;
}

void test1() {
    int x = 1;
    static_assert(
        std::is_reference_v<decltype(returnRef(x))>
        );
}

// decltype(auto) 作为非类型模板形参占位符
template<decltype(auto) N>
void foo2() {
    std::cout << N << std::endl;
}

void test2() {
    static const int x = 1;
    static int y = 2;
    foo2<x>();
    foo2<(x)>();
    // foo2<y>(); // compilation failed, y is not const
    foo2<(y)>();
}


int main(int argc, char const *argv[]) {
    test2();
    return 0;
}