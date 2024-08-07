#include <iostream>

struct Foo {
    int n = 0;
    void f() {
        [=, this] {
            n = 10;
        } ();
    }
};

int main(int argc, char *argv[]) {
    Foo f;
    f.f();
    std::cout << f.n << std::endl;
    return 0;
}