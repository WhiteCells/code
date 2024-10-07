#include <iostream>

struct A {
    virtual std::ostream &put(std::ostream &o) const { return o << 'A'; }
};

struct B : A {
    virtual std::ostream &put(std::ostream &o) const override {
        return o << 'B';
    }
};

std::ostream &operator<<(std::ostream &o, const A &a) { return a.put(o); }

int main(int argc, char *argv[]) {
    std::cout << "hello world";
    return 0;
}
