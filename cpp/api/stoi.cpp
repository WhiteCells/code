#include <iostream>
#include <string>

void test01() {
    std::string s = "0123";
    int i = std::stoi(s);
    std::cout << i << std::endl;
}

int main() {
    test01();
    return 0;
}