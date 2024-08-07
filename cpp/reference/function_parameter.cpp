#include <iostream>

class A {
public:
    A() : a_(*(new int(1))) {}
    void foo(int &a) {
        a_ = a;
    }

    void print() {
        std::cout << a_ << std::endl;
    }

private:
    int &a_;
};

int main(int argc, char *argv[]) {
    A classa;
    {
        int a = 10;
        classa.foo(a);
    }
    classa.print();
    return 0;
}