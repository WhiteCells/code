#include <iostream>

struct S {
    int y : 4 = 11;
    int z : 33 {7};
};

int main(int argc, char *argv[]) {
    std::cout << S().y << std::endl;
    std::cout << S().z << std::endl;

    return 0;
}