#include <iostream>

using namespace std;

class A {
public:
    A(int a) : a_(a) {
        
    }
    int getMember() {
        return a_;
    }
private:
    int a_;
};

int main() {
    // A a; // error 类 "A" 不存在默认构造函数
    return 0;
}