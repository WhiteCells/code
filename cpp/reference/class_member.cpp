#include <iostream>

class A {
public:
    A(int a) : x(a) {
        int a = 1;
        x = a;
    }

private:
    int &x;
};