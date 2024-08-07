#include <ostream>
#include <istream>
#include <string>
#include <iostream>

int main(int argc, char *argv[]) {
    std::string str {};
    std::ostream &out = std::cout;
    std::istream &in = std::cin;
    in >> str;
    out << str;
    return 0;
}