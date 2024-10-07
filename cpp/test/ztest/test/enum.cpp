#include <iostream>

class A {
public:
    enum TYPE {
        TYPE1,
        TYPE2,
    };
};

int main(int argc, char *argv[]) {
    A::TYPE a = A::TYPE1;
    return 0;
}