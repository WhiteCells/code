#include "thread_pool.h"
#include <iostream>
#include <vector>

int main(int argc, char *argv[]) {
    ThreadPool thread_pool(2);
    std::vector<std::future<int>> results;

    for (int i = 0; i < 8; ++i) {
        results.emplace_back(
            thread_pool.addTask([i] {
            std::cout << "A: " << i << std::endl;
            std::cout << "B: " << i << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            return i * i;
        }));
    }

    for (auto &&result : results) {
        std::cout << result.get() << " ";
    }
    std::cout << std::endl;
    
    return 0;
}