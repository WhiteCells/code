#include <iostream>
#include "config.h"

int main(int argc, char const *argv[]) {
    std::cout << CMAKE_CXX_STANDARD << std::endl;
    std::cout << PROJECT_SOURCE_DIR << std::endl;
    std::cout << CMAKE_VERSION << std::endl;
    return 0;
}