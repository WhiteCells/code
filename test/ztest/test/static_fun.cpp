#include <iostream>

static void foo() {
    std::cout << "foo" << std::endl;
}

static void test() {
    for (int i = 0; i < 10; ++i) {
        foo();
    }
}

int main(int argc, char *argv[]) {
    test();
    return 0;
}