#include <iostream>
#include <string>

using namespace std;

// 参数类型
void func1(int a, int b, string s) {
    cout << a + b << s << endl;
}

void func1(float a, float b, string s) {
    cout << a + b << s << endl;
}

// 参数个数
void func1(int a, int b, int c, string s) {
    cout << a + b + c << s << endl;
}

// 参数的顺序
void func1(string s, int a, int b, int c) {
    cout << s << a + b + c << endl;
}


template<class T>
void func2() {
    cout << "template func2()" << endl;
}

void func2() {
    cout << "func2()" << endl;
}

void test02() {
    func2<int>();
    func2();
}

void test01() {
    func1(1, 2, " func1");       // func1(int a, int b, string s)
    func1(1.1, 2, " func1");     // func1(int a, int b, string s)
    func1(1.1F, 2.1F, " func1"); // func1(float a, float b, string s)
    func1("func1 ", 1, 2, 3);    // func1(string s, int a, int b, int c)
}

int main() {
    test01();
    test02();
    return 0;
}