#include <iostream>
#include <thread>

int main(int argc, char *argv[]) {
    std::thread([]() {
        static int i = 0;
        while (1) {
            std::cout << "thread" << i++ << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }).detach();
    while (1) {}
    return 0;
}