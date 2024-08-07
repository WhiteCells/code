#include <iostream>

class {} A;
typedef class BB {
public:
    BB() {
        std::cout << "BB class" << '\n';
    }
}B;

void PrintEmptyClassSize() {
    std::cout << sizeof(A) << '\n';
    // A a; // error
    B b;
}

class C {
public:
    C(int val) {
        this->val = val;
        std::cout << "C()" << '\n';
    }
    C(const C& c) {
        this->val = c.val;
        std::cout << "C(const C&)" << '\n';
    }
    ~C() {
        std::cout << "~C()" << '\n';
    }
    int val;
};

void ClassC() {
    // C c(1);
    C c2(C(1));
}

class D {
public:
    int a;
    const int b = 10;
    D() {
        // std::cout << "D()" << '\n';
    }
    D(const D& d) {
        d.fun2();
        // d.fun1(); // error passing 'const D' as 'this' argument discards qualifiers
    }

    void fun1() {
        std::cout << "fun1()" << '\n';
    }

    void fun2() const { // const 函数只能访问变量和常量，不能修改，同时只能调用 const 修饰的函数。
        std::cout << "fun2()" << '\n';
        std::cout << a << '\n';
        std::cout << b << '\n';
        // fun1(); // error passing 'const D' as 'this' argument discards qualifiers
        // a = 10; // 表达式必须是可修改的左值
        // b = 10; // 表达式必须是可修改的左值
    }
};

void ClassD() {
    D d;
    D d2(d);
}


class E {
public:
    int a;
    const int b = 10;
    // 禁止非常量静态成员的类内初始化
    // static int c = 20; // error ISO C++ forbids in-class initialization of non-const static member 'E::c'
    static const int c = 20;
    static int d;
    E() {

    }
    // 静态成员函数不能直接访问非静态成员变量或非静态成员函数，
    // 因为它们不依赖于类的实例，只能访问属于类本身的静态成员
    static void sfun() {
        // 这是一个静态成员函数
        // 可以在函数中访问其他静态成员，但不能访问非静态成员
        // std::cout << b << '\n'; // error invalid use of member 'E::b' in static member function
        // 访问类中静态成员
        std::cout << "sfun()" << '\n';
        std::cout << c << '\n';
        std::cout << d << '\n';
    }
};

// 静态成员变量类外初始化
int E::d = 30;

void ClassE() {
    E e;
    e.sfun();
    // 通过类名访问类中静态成员
    E::sfun();
    E::c;
    E::d;
}

class F {
private:
    int a = 10;
public:
    int& fun() {
        return a;
    }
    int GetA() {
        return a;
    }
};

void ClassF() {
    F f;
    f.fun() = 20;
    std::cout << f.GetA() << '\n';
}

int main() {
    // PrintEmptyClassSize(); // 1
    // ClassC();
    // ClassD();
    // ClassE();
    ClassF();
    return 0;
}