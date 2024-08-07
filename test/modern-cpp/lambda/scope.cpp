#include <iostream>

int x = 1;

int main(int argc, char *argv[]) {
    int y = 1;
    static int z = 1;
    // auto foo = [x, y, z] {};
    auto foo = [y] { return x + y + z; };
    std::cout << foo() << std::endl;
    return 0;
}