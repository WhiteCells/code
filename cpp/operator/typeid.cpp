#include <iostream>
#include <vector>
#include <typeinfo>

void UseTypeid() {
    std::cout << typeid(10).name() << '\n';
    std::cout << typeid(11.1).name() << '\n';
    std::cout << typeid(12l).name() << '\n';
    int a = 10;
    std::cout << typeid(a).name() << '\n';
    class AClass {};
    std::cout << typeid(AClass).name() << '\n';

    struct BStruct {};
    std::cout << typeid(BStruct).name() << '\n';

    int d = 10;
    std::cout << typeid(d).name() << '\n';

    int &b = d;
    std::cout << typeid(b).name() << '\n';

    int *c = &b;
    std::cout << typeid(c).name() << '\n';
}

int main() {
    UseTypeid();
    return 0;
}