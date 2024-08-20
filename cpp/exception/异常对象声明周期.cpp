#include <iostream>

using namespace std;

class MyException {
public:
    MyException() {
        cout << "MyException()" << endl;
    }
    MyException(const MyException &) {
        cout << "MyException(const MyException &)" << endl;
    }
    ~MyException() {
        cout << "~MyException()" << endl;
    }
};

void func() {
    throw MyException();
    // throw new MyException();
}

void test01() {
    try {
        func();
    } catch (MyException ex) {
        cout << "异常捕获" << endl;
    }
}

void test02() {
    try {
        func();
    } catch (MyException &ex) {
        cout << "exception" << endl;
    }
}

void test03() {
    try {
        func();
    } catch (MyException *ex) {
        cout << "异常捕获" << endl;
        delete ex;
    }
}

int main() {
    test01();
    // test02();
    // test03();
    return 0;
}