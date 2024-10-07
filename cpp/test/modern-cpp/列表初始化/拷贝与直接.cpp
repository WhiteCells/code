#include <iostream>
#include <string>

struct C {
    C(std::string a, int b) {}
    C(int a) {}
};

void foo(C) {}

C bar() {
    return ("world", 0);
}

int main(int argc, char const *argv[]) {
    C x1 = {1}; // 拷贝初始化
    C x2 {2}; // 直接初始化
    C x3 = {"l", 3}; // 拷贝初始化
    C x4 {"l", 4}; // 直接初始化
    foo({5}); // 拷贝初始化
    foo({"l", 6}); // 拷贝初始化
    C x5 = bar(); // 拷贝初始化
    C *x6 = new C {"l", 7}; // 直接初始化
}
