#include <iostream>

class C {
    typedef long long ll1;
    using ui1 = unsigned int;
public:
    typedef long long ll2;
    using ui2 = unsigned int;
};

class D : C {
    // ll1 a = 1; // error
    ll2 b = 1;
    // ui1 c = 1; // error
    ui2 c = 1;
};

int main(int argc, char *argv[]) {
    return 0;
}