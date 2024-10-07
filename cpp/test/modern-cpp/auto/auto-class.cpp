#include <iostream>

class Base {
public:
    virtual void foo() {
        std::cout << "Base foo" << std::endl;
    }
};

class Derived : public Base {
public:
    void foo() override {
        std::cout << "Derived foo" << std::endl;
    }
};

int main(int argc, char const *argv[]) {
    Base *p = new Derived();

    auto v = *p;
    v.foo(); // "Base foo"

    auto pv = p;
    pv->foo(); // "Derived foo"

    auto &rv = *p;
    rv.foo(); // "Derived foo"

    auto &rp = p;
    p->foo(); // "Derived foo"

    return 0;
}

// #include <iostream>
// 
// class Base {
// public:
//     virtual void foo() {
//         std::cout << "Base foo" << std::endl;
//     }
// };
// 
// class Derived : public Base {
// // private:
// public:
//     void foo() {
//         std::cout << "Derived foo" << std::endl;
//     }
// };
// 
// int main(int argc, char const *argv[]) {
//     // Derived *pderived = new Derived();
//     // pderived->foo();
//     Base *p = new Derived();
//     p->foo(); // Derived foo
// 
//     Base b = Derived();
//     b.foo();
//     return 0;
// }