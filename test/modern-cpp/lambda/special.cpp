#include <iostream>

int main(int argc, char *argv[]) {
    int x = 1;
    auto foo = [=]() mutable {
        x += 1; // compilation failed
        std::cout << x << std::endl;
    };
    foo();
    foo();
    std::cout << x << std::endl;
    return 0;
}

// int main(int argc, char *argv[]) {
//     int x = 1;
//     auto foo = [&] {
//         x += 1;
//         return 0;
//     }();
//     std::cout << x << std::endl;
//     return 0;
// }