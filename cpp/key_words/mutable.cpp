#include <iostream>

struct X {
    X() { std::cout << "构造" << '\n'; }
    X(const X&) { std::cout << "拷贝" << '\n'; };
    ~X() { std::cout << "析构" << '\n'; };
    int a;
};

struct Y {
    mutable X x;
    Y() = default;

};

int main() {
    
}
