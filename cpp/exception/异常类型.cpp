#include <iostream>
#include <cstring>

using namespace std;

// 自定义的异常类
class MyException {
public:
    MyException(const char *str) {
        std::cout << "MyException()" << std::endl;
        error_ = new char[strlen(str) + 1];
        strcpy(error_, str);
    }
    MyException(const MyException &me) {
        std::cout << "MyException(const MyException &)" << std::endl;
        this->error_ = new char[strlen(me.error_) + 1];
        strcpy(this->error_, me.error_);
    }
    MyException &operator=(const MyException &me) {
        std::cout << "operator=(const MyException &)" << std::endl;
        if (this->error_ != NULL) {
            delete[] error_;
            error_ = NULL;
        }
        this->error_ = new char[strlen(me.error_) + 1];
        strcpy(this->error_, me.error_);
        return *this;
    }
    void what() const {
        cout << error_ << endl;
    }
    ~MyException() {
        std::cout << "~MyException()" << std::endl;
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
    } catch (const MyException &e) {
        e.what(); // 调用异常对象
    }
}

int main() {
    test();
    return 0;
}