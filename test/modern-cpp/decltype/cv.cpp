#include <iostream>

struct A {
    int x;
};

void foo() {
    const int i = 0;
    decltype(i) i2 = 0; // const int i2 = 0;
    const struct A a = A();
    decltype(a.x) i3 = 0; // int i3 = 0;
    decltype((a.x)) i4 = 0; // const int &i4 = 0; 
}

int main(int argc, char const *argv[]) {
    
    return 0;
}