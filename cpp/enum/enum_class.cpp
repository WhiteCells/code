#include <iostream>

enum class STATUS {
    ERROR1,
    ERROR2,
    ERROR3,
};

enum class STATUS2 : int {
    ERROR1,
    ERROR2,
    ERROR3,
};

enum CODE1 {
    CODE1_ERROR1,
    CODE1_ERROR2,
    CODE1_ERROR3,
};

enum CODE2 {
    // CODE1_ERROR1,
    CODE2_ERROR1,
    CODE2_ERROR2,
    CODE2_ERROR3,
};

int main(int argc, char *argv[]) {
    // std::cout << STATUS::ERROR1 << std::endl;
    // printf("%d\n", (int)STATUS::ERROR1);
    printf("%d\n", STATUS2::ERROR1);
    // std::cout << CODE1_ERROR1 << std::endl;
    return 0;
}