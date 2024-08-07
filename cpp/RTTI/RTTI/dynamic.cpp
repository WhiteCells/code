#include <iostream>

class Base {};

class Derive : public Base {};

int main() {
    Derive *derive = new Derive();
    Base *base = dynamic_cast<Base *>(derive);

    delete base;
    return 0;
}