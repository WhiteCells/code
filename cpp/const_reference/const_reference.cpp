#include <iostream>

class A {
public:
    A() { std::cout << "A()" << std::endl; }
    A(const A &) { std::cout << "A(const A &)" << std::endl; }
    A(A &&) { std::cout << "A(A &&)" << std::endl; }
    ~A() { std::cout << "~A()" << std::endl; }
    A &operator=(const A &) {
        std::cout << "operator=" << std::endl;
        return *this;
    }
    A &operator=(A &&) {
        std::cout << "operator=(A &&)" << std::endl;
        return *this;
    }
};

const A &getConstReference() {
    static A a;
    return a;
    // return A();
}

A get() {
    A a;
    return a;
}

const std::string &getString() {
    return "string";
}

int main(int argc, char *argv[]) {
    // A a = getConstReference();
    // const A &a = getConstReference();
    // A a3 = std::move(A());

    // A a = get();

    // 延长临时对象的声明周期
    // const std::string &res1 = getString();
    // 临时对象在返回后会销毁
    // std::string res2 = getString();

    return 0;
}