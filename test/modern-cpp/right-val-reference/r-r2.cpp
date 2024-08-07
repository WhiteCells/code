#include <iostream>
#include <string.h>
#include <chrono>

class MemoryPool {
public:
    MemoryPool() : pool_(new char[pool_size]) {}
    MemoryPool(const MemoryPool &other) : pool_(new char[pool_size]) {
        // std::cout << "copy memory pool" << std::endl;
        memcpy(pool_, other.pool_, pool_size);
    }
    MemoryPool(MemoryPool &&other) {
        // std::cout << "move memory pool" << std::endl;
        pool_ = other.pool_;
        other.pool_ = nullptr;
    }
    ~MemoryPool() {
        if (pool_ != nullptr) {
            delete[] pool_;
        }
    }
private:
    char *pool_;
    static const int pool_size = 4096;
};

MemoryPool getMemoryPool(const MemoryPool &pool) {
    return pool;
}

MemoryPool makePool() {
    MemoryPool pool;
    return getMemoryPool(pool);
}

int main(int argc, char const *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000000; ++i) {
        MemoryPool pool = makePool();
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;
    std::cout << "time: " << diff.count() << " s" << std::endl;
    return 0;
}