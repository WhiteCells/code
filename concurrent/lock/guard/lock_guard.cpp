#include <mutex>
#include <thread>
#include <iostream>

int a = 10;
std::mutex mtx;

int main(int argc, char *argv[]) {
    std::thread([] {
        {
            std::lock_guard<std::mutex> lock(mtx);
            a = 20;
        }
    }).detach();

    std::thread([] {
        {
            std::lock_guard<std::mutex> lock(mtx);
            a = 30;
        }
    }).detach();

    std::cout << a << std::endl;
    return 0;
}