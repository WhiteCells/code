#include <iostream>
#include <cstring>

using namespace std;

// 自定义的异常类
class MyException {
public:
    MyException(const char *str) {
        error_ = new char[strlen(str) + 1];
        strcpy(error_, str);
    }
    MyException(const MyException &me) {
        this->error_ = new char[strlen(me.error_) + 1];
        strcpy(this->error_, me.error_);
    }
    MyException &operator=(const MyException &me) {
        if (this->error_ != NULL) {
            delete[] error_;
            error_ = NULL;
        }
        this->error_ = new char[strlen(me.error_) + 1];
        strcpy(this->error_, me.error_);
        return *this;
    }
    void what() {
        cout << error_ << endl;
    }
    ~MyException() {
        if (error_ != NULL) {
            delete[] error_;
            error_ = NULL;
        }
    }
public:
    char *error_;
};

void foo() {
    throw MyException("exception"); // 抛出匿名对象异常
}

void test() {
    try {
        foo();
    } catch (MyException e) {
        e.what(); // 调用异常对象
    }
}

int main() {
    test();
    return 0;
}