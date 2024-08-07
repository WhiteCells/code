#include <iostream>

using namespace std;

class A {
    friend ostream &operator<<(ostream &cout, const A &p);
public:
    A(int a, int b) : m_a(a), m_b(b) {}
private:
    int m_a;
    int m_b;
};

// operator<< 不能写在成员函数, 要写在全局函数
ostream &operator<<(ostream &os, const A &p) {
    os << p.m_a << p.m_b << endl;
    return os;
}

void test01() {
    operator<<(cout, A(1, 1)) << (cout, A(2, 2)) << (cout, A(3, 3));
    cout << A(1, 1) << A(2, 2) << A(3, 3);
}

int main() {
    test01();
    return 0;
}