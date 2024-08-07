#include <iostream>
#include <cstring>
#include <stdexcept>

using namespace std;

// 继承异常类
class MyOutOfRange : public exception {
public:
    MyOutOfRange(const char *error) {
        this->error_ = new char[strlen(error) + 1];
        strcpy(this->error_, error);
    }
    ~MyOutOfRange() {
        if (error_ != NULL) {
            delete[] error_;
            error_ = NULL;
        }
    }
    const char *what() const noexcept override {
        return error_;
    }
public:
    char *error_;
};

void func01() {
    throw MyOutOfRange("except");
}

void test01() {
    try {
        func01();
    }
    catch (exception &e) {
        cout << e.what() << endl;
    }
}

int main() {
    test01();
    return 0;
}
