#include "func.h"
#include <iostream>

int main(int argc, char *argv[])
{
    std::cout << __func__ << std::endl;
    func();
    return 0;
}