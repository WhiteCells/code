#include <iostream>

struct A {
    A() {
        // std::cout << "A::A()" << std::endl;
        foo();
    }
    virtual ~A() {
        // std::cout << "A::~A()" << std::endl;
        foo();
    }
    virtual void foo() {
        // std::cout << "A::foo()" << std::endl;
        std::cout << "1";
    }
    void bar() {
        // std::cout << "A::bar()" << std::endl;
        foo();
    }
};

struct B : public A {
    virtual void foo() {
        // std::cout << "B::foo()" << std::endl;
        std::cout << "2";
    }
};

int main() {
    B b;
    b.bar();
}

/*
Even though foo() is virtual, it is not considered to be so during the execution
of constructors and destructors.

Rationale:

If an object of type B is being constructed, first the constructor
of A is called, then the constructor of B. Thus, during A's constructor,
the "B part" of the object has not been constructed yet, and should not be used.
One could easily imagine that B::foo() would use the "B part" of the object,
so it would be dangerous for A's constructor to call it.

When the object is destroyed, B's destructor is called first,
then A's destructor, leading to the same problem.
 */