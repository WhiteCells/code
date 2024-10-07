#include <string>
#include <iostream>

int main(int argc, char *argv[]) {
    const char *cstr = "hello";
    std::string str(cstr, 2);
    std::cout << str << std::endl;
    return 0;
}