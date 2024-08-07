#include <iostream>

using namespace std;

// 自定义异常类
class MyException {
public:
    // 有参构造
    MyException() {
        cout << "构造函数" << endl;
    }
    // 拷贝构造
    MyException(const MyException& me) {
        cout << "拷贝构造" << endl;
    }
    ~MyException() {
        cout << "析构函数" << endl;
    }
};

void func() {
    // throw& (MyException()); // 创建匿名对象，调用构造
    throw new MyException();
}

//void test01() {
//
//    // 普通元素，异常对象 catch 处理完后就析构
//    try {
//        func();
//    }
//    catch (MyException ex) // 调用拷贝构造
//    {
//        cout << "异常捕获" << endl;
//    }
//}
//
//void test02() {
//
//    // 引用 不用调用拷贝构造，异常对象catch处理完析构
//    try {
//        func();
//    }
//    catch (MyException& ex) // 不调用拷贝构造
//    {
//        cout << "异常捕获" << endl;
//    }
//}

void test03() {
    
    // 指针，抛异常的时候就要抛出地址
    try {
        func();
    }
    catch (MyException* ex) {
        cout << "异常捕获" << endl;
        delete ex;
    }
}

int main() {
    test03();
    return 0;
}