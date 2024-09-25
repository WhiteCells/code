#include "thread_pool.hpp"
#include <iostream>

int main(int argc, char *argv[]) {
    std::vector<std::future<int>> proms;
    ThreadPool pool;
    for (int i = 0; i < 20; ++i) {
        proms.emplace_back(pool.addTask([](int num) -> int {
            std::cout << "thread: " << num << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            return num * num;
        }, i));
    }
    for (auto &p : proms) {
        std::cout << "ret: " << p.get() << std::endl;
    }
    return 0;
}