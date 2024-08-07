#include<iostream>
using namespace std;

// 这个函数只能抛出 int，float，char 三种类型异常
// 抛出其他类型就会报错
// C++17 中，这种动态异常规范是不允许的
// void foo1() throw(int, float, char) {
//     throw 1;
// }

// 空异常规范表示函数可以抛出任何类型的异常
void foo2() throw() {
    try {
        throw 1;
    } catch (...) {
        std::cout << "except" << std::endl;
    }
}

// 可以抛出任何异常
void foo3() {

}

int main() {
    try {
        foo2();
    } catch (char *str) {
        cout << "hello" << str << endl;
    } catch (...) { // 捕获所有异常
        cout << "未知类型异常" << endl;
    }
    return 0;
}