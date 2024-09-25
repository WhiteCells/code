#include <future>
#include <thread>
#include <iostream>

int main(int argc, char *argv[]) {
    std::future<int> res = std::async([]() -> int {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        return 1;
    });

    std::cout << "main1 ..." << std::endl;
    res.wait();
    std::cout << "main2 ..." << std::endl;
    res.wait();
    std::cout << "main3 ..." << std::endl;
    res.wait();
    std::cout << "main4 ..." << std::endl;
    std::cout << res.get() << std::endl;
    return 0;
}