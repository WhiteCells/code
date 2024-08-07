#include <iostream>

using namespace std;

void foo1(int a, int b) {
    cout << a + b << endl;
}

void foo1(int a, int b, int) { // int 为占位符, 需要在调用函数时传参
    cout << a - b << endl;
}

void foo2(int a, int) {
    cout << a << endl;
}

void test01() {
    foo1(10, 20);
    foo1(10, 20, 0);
    
    foo2(10, 0);
}

int main() {
    test01();
    return 0;
}