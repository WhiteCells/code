#include<iostream>
#include<string>
using namespace std;

class Person {
public:
    int m_A;
    int m_B;
};
// 全局函数重载 + 
Person operator+(Person& p1, Person& p2) {
    Person temp;
    temp.m_A = p1.m_A + p2.m_A;
    temp.m_B = p2.m_B + p2.m_B;
    return temp;
}
// 全局函数重载不同类型的加号
Person operator+(Person& p1, int num) {
    Person temp;
    temp.m_A = p1.m_A + num;
    temp.m_B = p1.m_B + num;
    return temp;
}
void test() {
    Person p1;
    p1.m_A = 10;
    p1.m_B = 10;
    Person p2;
    p2.m_A = 20;
    p2.m_B = 20;

    Person p3 = p1 + p2;

    Person p4 = p1 + 40;

    cout << "p3 m_A: " << p3.m_A << endl;
    cout << "p3 m_B: " << p3.m_B << endl;
    cout << "p4 m_B: " << p4.m_B << endl;
    cout << "p4 m_B: " << p4.m_B << endl;
}

int main() {
    test();
    return 0;
}


