#include <thread>
#include <iostream>

int main(int argc, char *argv[]) {
    int i = 0;
    std::thread my_thread([&](int i) {
        std::cout << i << std::endl;
    }, i);
    my_thread.join();
    return 0;
}