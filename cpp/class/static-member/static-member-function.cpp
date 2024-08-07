#include <iostream>

class A {
public:
    static void foo();

    // called by foo
    static void test1();

    // called by foo (failed)
    void test2();

    // call foo
    void callfoo();

    int x = 1;
    const int y = 2;
    static constexpr int z = 1;
};

void A::foo() {
    std::cout << "static void foo()" << std::endl;
    // std::cout << x << std::endl; // compilation failed
    // std::cout << y << std::endl; // compilation failed
    std::cout << z << std::endl;

    test1();
    // test2(); // compilation failed
}

void A::test1() {
    std::cout << "test1" << std::endl;
}

void A::test2() {
    std::cout << "test2" << std::endl;
}

void A::callfoo() {
    foo();
}

int main(int argc, char const *argv[]) {
    // class name access
    A::foo();

    // object access
    A a;
    a.foo();
    a.test1();

    return 0;
}
