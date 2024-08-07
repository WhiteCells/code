#include "singleton.h"
#include <iostream>

int main(int argc, char *argv[]) {
    Singleton *instance1 = Singleton::getInstance();
    Singleton *instance2 = Singleton::getInstance();

    std::cout << (instance1 == instance2 ? "same" : "not the same") << std::endl;
    return 0;
}