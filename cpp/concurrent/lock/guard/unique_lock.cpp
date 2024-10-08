#include <mutex>
#include <iostream>
#include <vector>
#include <thread>

std::mutex mtx;
int data = 0;

void use_unique_lock() {
    std::unique_lock<std::mutex> lock(mtx);
    data += 10000;
    lock.unlock();
}

void test_use_unique_lock() {
    std::vector<std::thread> threads;
    for (size_t i = 0; i < 10; ++i) {
        threads.emplace_back(use_unique_lock);
    }
    for (auto &t : threads) {
        t.join();
    }
    std::cout << data << std::endl;
}

void use_owns_lock_api() {
    std::unique_lock<std::mutex> lock(mtx);
    ++data;
    if (lock.owns_lock()) {
        std::cout << "lock.owns_lock()" << std::endl;
    }
    lock.unlock();
    if (!lock.owns_lock()) {
        std::cout << "!lock.owns_lock()" << std::endl;
    }
    lock.lock();
    if (lock.owns_lock()) {
        std::cout << "lock.owns_lock()" << std::endl;
    }
}

void defer_lock() {
    std::unique_lock<std::mutex> lock(mtx, std::defer_lock);
    std::cout << lock.owns_lock() << std::endl; // 0
    lock.lock(); // defer lock
    std::cout << lock.owns_lock() << std::endl; // 1
    ++data;
    lock.unlock();
    std::cout << lock.owns_lock() << std::endl; // 0
}

void adopt_lock() {
    // mtx.lock();
    std::unique_lock<std::mutex> lock(mtx, std::adopt_lock);
    std::cout << lock.owns_lock() << std::endl;
}

int main(int argc, char *argv[]) {
    // test_use_unique_lock();
    // use_owns_lock_api();
    // defer_lock();
    // adopt_lock();
    return 0;
}