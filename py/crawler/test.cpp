#include <iostream>
#include <string>

std::string foo()
{
    std::cout << __func__ << std::endl;
    return "foo";
}

int main(int argc, char *argv[]) {
    foo();
    return 0;
}