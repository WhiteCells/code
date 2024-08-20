#include <iostream>
#include <cstring>
#include <stdexcept>

using namespace std;

// 继承异常类
class MyOutOfRange : public exception {
public:
    MyOutOfRange(const char *error) {
        error_ = new char[strlen(error) + 1] {};
        strcpy(error_, error);
    }
    // new
    MyOutOfRange(const MyOutOfRange &other) {
        if (this == &other) {
            return;
        }
        if (error_) {
            delete[] error_;
        }
        error_ = new char[strlen(other.error_) + 1] {};
        strcpy(error_, other.error_);
    }
    ~MyOutOfRange() {
        if (error_) {
            delete[] error_;
            error_ = NULL;
        }
    }
    virtual const char *what() const noexcept override {
        return error_;
    }

private:
    char *error_;
};

void foo() {
    // throw new MyOutOfRange("except");
    throw MyOutOfRange("except");
}

void test01() {
    try {
        foo();
    } catch (MyOutOfRange *e) {
        cout << e->what() << endl;
        delete e;
    }
}

void test02() {
    try {
        foo();
    } catch (const MyOutOfRange &e) {
        cout << e.what() << std::endl;
    }
}

int main() {
    test01();
    return 0;
}
