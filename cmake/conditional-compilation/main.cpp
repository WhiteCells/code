#ifdef USE_TEST1
#include "test1.h"
#endif
#include "test2.h"
#include <iostream>

int main(int argc, char const *argv[]) {
#ifdef USE_TEST1
    test1();
#endif
    test2();
    return 0;
}