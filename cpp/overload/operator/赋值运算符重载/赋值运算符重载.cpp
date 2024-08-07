#include<iostream>
using namespace std;

class A {
public:
    A(int age) : m_a(new int(age)) {}
    ~A() {
        if (m_a != NULL) {
            delete m_a;
            m_a = NULL;
        }
    }
    // 重载 赋值=
    // operator= 只能在类中重载(结构体不行)
    A &operator=(A &p) {
        // 先判断是否有属性在堆区
        // 有先释放
        // 再深拷贝
        if (m_a != NULL) {
            delete m_a;
            m_a = NULL;
        }
        m_a = new int(*p.m_a);
        // 返回对象本体
        return *this;
    }
    int *m_a;
};

void test1() {
    A a1(18);
    A a2(20);
    A a3(30);

    // a1.operator=(a2) = a3;
    a2 = a1 = a3;

    cout << *a1.m_a << endl;
    cout << *a2.m_a << endl;
    cout << *a3.m_a << endl;
}

int main() {
    test1();
    return 0;
}