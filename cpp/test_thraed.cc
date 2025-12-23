#include <thread>
#include <iostream>

int main(int argc, char *argv[])
{
    std::thread([]() {
        std::cout << "hello thread" << std::endl;
    }); // join or detach

    // while (1) {
    // }
    return 0;
}