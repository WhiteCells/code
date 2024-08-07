#include <iostream>

void test01() {
    const char *c = "0123";
    int i = atoi(c);
    std::cout << i << std::endl;
}

int main() {
    test01();
    return 0;
}