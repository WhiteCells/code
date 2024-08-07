#include <iostream>
using namespace std;

class A {
public:
    A() {
        cout << "A()" << endl;
    }
    ~A() {
        cout << "~A()" << endl;
    }
};

int divide(int x, int y) {
    A a;
    if (!y) {
        throw y;
    }
    cout << "----" << endl;
    return x / y;
}

int main() {
    try {
        divide(10, 0);
    } catch (int) {
        cout << "dividend by 0" << endl;
    }
    return 0;
}