#include <iostream>
#include <memory>
#include <vector>

class C {
public:
    void foo() {
        std::cout << "A";
    }
    void foo() const {
        std::cout << "B";
    }
};

struct S {
    std::vector<C> v;
    std::unique_ptr<C> u;
    C *const p1;
    C const *p2;

    S() : v(1), u(new C()), p1(u.get()), p2(u.get()) {

    }
};

int main() {
    S s;
    s.v[0].foo(); // A
    s.u->foo(); // A
    s.p1->foo(); // A
    s.p2->foo(); // B
    
    const S &r = s;
    r.v[0].foo(); // B
    r.u->foo(); // A
    r.p1->foo(); // A
    r.p2->foo(); // B
}