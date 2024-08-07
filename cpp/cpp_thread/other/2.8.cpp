#include <thread>
#include <iostream>
#include <vector>

int main(int argc, char *argv[]) {
    std::vector<std::thread> threads;

    for (int i = 0; i < 10; ++i) {
        threads.emplace_back([](int i) {
            std::cout << "thead " << i << std::endl;
        }, i);
    }

    for (auto &thread : threads) {
        thread.join();
    }
    
    return 0;
}