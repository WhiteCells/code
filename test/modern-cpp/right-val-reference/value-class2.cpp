#include <iostream>

class A {
public:
    A() {}
    ~A() { std::cout << "~A()" << std::endl; }
    int x = 1;
};

int main(int argc, char const *argv[]) {
    A a;
    {
        // A &&a1 = a; // compilation
        A &&a2 = static_cast<A &&>(a);
        a2.x = 2;
    }
    std::cout << a.x << std::endl;
    std::cout << "---" << std::endl;
    return 0;
}