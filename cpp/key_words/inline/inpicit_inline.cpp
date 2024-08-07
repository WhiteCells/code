#include <iostream>

class A {
public:
    void foo(); // 声明不会隐式内联
    void foo2() {} // 隐式内联

    static void foo3(); // 声明不会隐式内联
    static void foo4() {} // 隐式内联
};

inline void A::foo3() {

}

inline void foo() {
    
}

int main(int argc, char *argv[]) {
    
    return 0;
}