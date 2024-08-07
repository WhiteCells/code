#include <iostream>
#include <string.h>

class MemoryPool {
public:
    MemoryPool() : pool_(new char[pool_size]) {}
    MemoryPool(const MemoryPool &other) : pool_(new char[pool_size]) {
        std::cout << "copy memory pool" << std::endl;
        memcpy(pool_, other.pool_, pool_size);
    }
    MemoryPool(MemoryPool &&other) {
        std::cout << "move memory pool" << std::endl;
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

void movePool(MemoryPool &&pool) {
    // MemoryPool p(pool);
    MemoryPool p(static_cast<MemoryPool &&>(pool));
    MemoryPool p(std::move(pool));
}

int main(int argc, char const *argv[]) {
    movePool(MemoryPool());
    return 0;
}

