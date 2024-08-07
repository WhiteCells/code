#include <iostream>

struct X {
    int a;
};

class A {
public:
    A() {}
    ~A() { std::cout << "~A()" << std::endl; }
    int x = 1;
};

int main(int argc, char const *argv[]) {
    int b = X().a;
    int i = 0;
    // int &&x = i; // compilation failed
    int &&y = static_cast<int &&>(i);

    A a;
    {
        A &&a2 = static_cast<A &&>(a);
        a2.x = 2;
    }
    std::cout << "---" << std::endl;
    std::cout << a.x << std::endl;
    return 0;
}