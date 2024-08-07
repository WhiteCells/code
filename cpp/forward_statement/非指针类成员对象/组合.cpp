#include <iostream>
#include <memory>

class B;

class A {
private:
    // B b;
    // B &rb;
    std::shared_ptr<B> bptr;
    B *b;
};

class B {};

int main(int argc, char *argv[]) {
    A a;
    return 0;
}