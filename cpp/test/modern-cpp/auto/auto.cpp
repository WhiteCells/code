#include <iostream>

// item 1
void foo1() {
    int a = 1;
    // auto *pa = &a, b = 2.0; // compilation failed
}

struct Type1 {
    // auto y = 2;
};

struct Type2 {
    static const auto y = 2;
};

struct Type3 {
    static inline auto z = 2; // C++17
};

void foo(auto x) {} // C++20

auto f = [](auto x) {}; // C++14

void foo() {
    const int i = 1;
    auto a = i;       // auto 推导为 int，a 推导为 int
    auto &b = i;      // auto 推导为 const int，b 推导为 const int &
    auto *c = &i;     // auto 推导为 const int，c 推导为 const int *
    const auto d = i; // auto 推导为 int，d 推导为 const int
}

int a[3];
void func(int) {}

auto pf = func;
void(__cdecl *pf2)(int) = func;


void foo2() {
    auto v1 = {1, 2, 3};
    int i = 0;
    int &a = i;
    auto v2 {a};
}

void foo3() {
    int i = 1;
    int &ri = i;
    auto x = ri;
    int *pi = &i;
    auto x = pi;
}


int main(int argc, char const *argv[]) {
    // foo1();
    return 0;
}