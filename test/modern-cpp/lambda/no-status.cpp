#include <iostream>

int main(int argc, char *argv[]) {
    auto f1 = [](void(*)()) {};
    f1([] {});

    auto f2 = [](void(&)()) {};
    f2(*[] {});
    int a = 1;
    auto f3 = [](auto a) {
        using T = typename decltype(a)::value_type;
        std::cout << decltype(a)::value_type << std::endl;
    };
    return 0;
}