#include <iostream>

void foo() {}
void foo(int) {}

struct A { void foo() {} };

int main() {
    // 全局查找
    foo();

    // 通过参数确定函数调用
    foo(1);

    // 通过对象类型、指正类型确定函数调用
    A a1;
    a1.foo();
    A *a2 = new A();
    a2->foo();
    return 0;
}