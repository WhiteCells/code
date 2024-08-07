#include <iostream>


void ModifyConst() {
    const int const_val = 10;
    int& no_const_val = const_cast<int&>(const_val);
    no_const_val = 20;
    std::cout << const_val << '\n';
    std::cout << no_const_val << '\n';
}

class A {
public:
    static const int a = 10;
    const int b;
    
};


int main() {
    ModifyConst();
    return 0;
}