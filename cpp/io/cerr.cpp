#include <iostream>

void test_cerr() {
    std::cerr << "test";
    std::cerr << "test";
    while (1) {}
}

void test_cout() {
    std::cout << "test";
    while (1) {}
}

int main(int argc, char *argv[]) {
    test_cerr();
    // test_cout();
    return 0;
}