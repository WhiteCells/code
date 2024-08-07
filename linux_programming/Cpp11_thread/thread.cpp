#include <thread>
#include <iostream>
#include <unistd.h>

void foo() {
    sleep(5);
}

int main(int argc, char *argv[]) {
    std::thread t1(foo);
    t1.join();
    std::cout << "main" << std::endl;
    return 0;
}