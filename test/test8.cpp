#include <iostream>

class S {
public:
    int a = 1;
    char c = '1';
};

class A {
public:
    void setA(int val) {
        val = val;
        // this->val = val;
    }
    S s;
    int val = 10;
    double val2 = 0;
    unsigned long long val3 = 0;
};

class C {
    typedef long long ll1;
    using ui1 = int;
public:
    typedef long long ll2;
    using ui2 = int;
    
    void foo(ui1 val);
};

int main(int argc, char *argv[]) {
    A a;
    a.setA(20);
    std::cout << a.val << std::endl;
    std::cout << alignof(a) << std::endl;
    std::cout << sizeof(a) << std::endl;
    return 0;
}