#include <iostream>

using namespace std;

void foo(int a, int b = 20, int c = 30) {
    cout << a << " " << b << " " << c << endl;
}

// 在同一作用域中，不能先声明带有默认参数的函数，然后再声明其它重载版本的函数。否则编译器无法区分具体要调用哪个函数。
// void foo(int a) {}
// void foo(int a, int b) {}
// void foo(int a, int b, int c) {}

void test1() {
    foo(10);
    foo(10, 30);
    foo(10, 40, 70);
}

void foo2() {
    cout << "foo()" << endl;
}
void foo2(int) {
    cout << "foo(int)" << endl;
}

void test2() {
    foo2(); // foo()
    foo2(1); // foo(int)
}

// 某个参数指定了默认值，则其后的所有参数都必须有默认值
// void foo3(int a = 10, int b, int c) {}

int main() {
    test1();
    test2();
    return 0;
}