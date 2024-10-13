#include <iostream>
#include <thread>

void foo() {
    while (1) {
        std::printf("foo\n");
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

int main(int argc, char *argv[]) {
    // std::thread([]() {
    //     while (1) {
    //         std::cout << "sub" << std::endl;
    //         std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    //     }
    // }).join();

    // std::thread([]() {
    //     while (1) {
    //         std::cout << "sub" << std::endl;
    //         std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    //     }
    // }).detach();

    std::thread t2(foo);
    // t2.join();
    while (1) {
        std::cout << "main" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    t2.join();
    // t2.detach();
    return 0;
}