#include <iostream>
#include <functional>

void test01(int a = 10) {
    bool i = [&](int b) {
        return a > b;
    }(30);
    std::cout << i << std::endl;
}

void test02() {
    std::function<int(int, bool)> f1 = [&](int a, bool b) {
        return 1; // 不加 ->int 必须需要返回值, 否则编译不通过
    };
    std::function<int(int, bool)> f2 = [&](int a, bool b)->int {
        return 1;
    };
    auto f3 = [&](int a, bool b) {
        if (b) {
            std::cout << a << std::endl;
        }
        return a;
    };
    f3(20, true);
}

int main() {
    test01();
    test02();
    return 0;
}