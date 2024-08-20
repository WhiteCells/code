#include "global.h"
#include <iostream>

extern void global() {
    std::cout << "global" << std::endl;
}