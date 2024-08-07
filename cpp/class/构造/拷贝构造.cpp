#include <iostream>

class Base {
public:
    Base() {}

    Base(const Base &other) {}

    Base &operator=(Base other) {
        return *this;
    }
};

int main(int argc, char *argv[]) {
    Base b;
    b = Base();
    Base b2(b);
    return 0;
}