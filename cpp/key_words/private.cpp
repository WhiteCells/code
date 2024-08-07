#include <iostream>

class A {
public:
    void print() {
        std::cout << val_ << std::endl;
    }

private:
    int val_ = 10;
};

int &foo(A &a);

template<int A::*val_>
class Tmp {
public:
    friend int &foo(A &a) {
        return a.*val_;
    }
};

// 实例化模板
template class Tmp<&A::val_>;

int main(int argc, char *argv[]) {
    A a;
    foo(a) = 20;
    a.print();
    return 0;
}