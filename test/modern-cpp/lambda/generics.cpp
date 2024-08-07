#include <iostream>
#include <string>

int main(int argc, char *argv[]) {
    auto foo = [](auto a) { return a; };
    int i = foo(1);
    std::string str = foo("string");
    std::cout << str << i << std::endl;
    return 0;
}