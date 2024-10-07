#include <iostream>
#include <string.h>

class MemoryPool {
public:
    MemoryPool() : pool_(new char[pool_size]) {}
    // 复制构造
    MemoryPool(const MemoryPool &other) : pool_(new char[pool_size]) {
        std::cout << "copy memory pool" << std::endl;
        memcpy(pool_, other.pool_, pool_size);
    }
    // 移动构造
    MemoryPool(MemoryPool &&other) {
        std::cout << "move memory pool" << std::endl;
        pool_ = other.pool_;
        other.pool_ = nullptr;
    }
    // 复制赋值
    MemoryPool &operator=(const MemoryPool &other) {
        std::cout << "copy(operator=) memory pool" << std::endl;
        memcpy(pool_, other.pool_, pool_size);
        return *this;
    }
    // 移动赋值
    MemoryPool &operator=(MemoryPool &&other) {
        std::cout << "move(operator=) memory pool" << std::endl;
        if (pool_ != nullptr) {
            delete[] pool_;
        }
        pool_ = other.pool_;
        other.pool_ = nullptr;
        return *this;
    }
    ~MemoryPool() {
        if (pool_ != nullptr) {
            delete[] pool_;
        }
    }
private:
    char *pool_;
    const static int pool_size = 4096;
};

MemoryPool getMemoryPool(const MemoryPool &pool) {
    return pool;
}

MemoryPool makeMemoryPool() {
    MemoryPool pool;
    return getMemoryPool(pool);
}

int main(int argc, char const *argv[]) {
    MemoryPool pool;
    pool = makeMemoryPool();
    return 0;
}