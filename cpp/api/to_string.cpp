#include <iostream>
#include <string>

void foo() {
    std::string str = std::to_string(1000);
    std::cout << str << std::endl;
    auto i = std::stoi(str);
    std::cout << i << std::endl;
}

int main(int argc, char const *argv[]) {
    foo();
    return 0;
}