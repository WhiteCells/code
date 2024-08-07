#include<iostream>
using namespace std;

class MyInteger {
    friend ostream &operator<<(ostream &cout, MyInteger myint);
public:
    MyInteger() {
        m_Num = 0;
    }
    // 前置递增
    MyInteger &operator++() {
        m_Num++;
        return *this;
    }
    // 后置递增 
    MyInteger operator++(int) {
        // 记录值
        MyInteger temp = *this;
        // 递增
        m_Num++;
        // 返回记录值
        return temp;
    }
private:
    int m_Num;
};

// &
ostream &operator<<(ostream &cout, MyInteger myint){
    cout << myint.m_Num;
    return cout;
}

void test1() {
    MyInteger myint1;
    cout << myint1 << endl;
    cout << myint1++ << endl;
    cout << myint1 << endl;
}

void test2() {
    MyInteger myint2;
    cout << myint2 << endl;
    cout << ++myint2 << endl;
}

int main() {
    test1();
    return 0;
}