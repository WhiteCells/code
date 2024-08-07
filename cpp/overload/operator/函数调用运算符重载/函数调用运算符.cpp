#include <iostream>
#include <string>
using namespace std;

// 打印输出类
class MyPrint {
public:
    void operator()(string text) {
        cout << text << endl;
    }
};

void MyPrint2(string text) {
    cout << text << endl;
}

void test1() {
    MyPrint myPrint;
    myPrint("hello world"); // 仿函数
    MyPrint2("hello world"); // 自定义函数
}

class MyAdd {
public:
    int operator()(int num1, int num2) {
        return (num1 + num2);
    }
};

void test2() {
    MyAdd add;
    cout << add(10, 20) << endl;
    cout << MyAdd()(20, 20) << endl; // 匿名函数对象
}

int main() {
    test1();
    test2();
    system("pause");
    return 0;
}