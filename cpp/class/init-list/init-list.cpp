#include<iostream>
using namespace std;

class A {
public:
    A() : x(10), y(20), z(30) {}
    A(int x, int y, int z) : x(x), y(y), z(z) {}
    void Print() { cout << x << " " << y << " " << z << " " << endl; }
private:
    int x;
    int y;
    int z;
};

void test01() {
    A a;
    a.Print();
}

void test02() {
    A a(1, 2, 3);
    a.Print();
}

int main() {
    test01();
    test02();
    return 0;
}