#include <atomic>
#include <thread>
#include <vector>
#include <iostream>

/**
 * C++ 内存模型允许编译器对代码进行优化，例如重排序指令，
 * 可能导致多个线程看到不同的初始化结果。
 */
// std::atomic<bool> lock = false; // error

// std::atomic<bool> lock(false);

std::atomic<bool> lock;
// std::atomic_init(&lock, false);


class SpinLock {
public:
    SpinLock() : flag_(ATOMIC_FLAG_INIT) {}

    void lock() {
        while (flag_.test_and_set(std::memory_order_acquire)) {

        }
    }

    void unlock() {
        flag_.clear(std::memory_order_release);
    }

private:
    std::atomic_flag flag_;
};

int cnt = 0;
SpinLock spin_lock;

void foo(int n) {
    for (int i = 0; i < n; ++i) {
        spin_lock.lock();
        ++cnt;
        spin_lock.unlock();
    }
}

int main(int argc, char *argv[]) {
    std::vector<std::thread> threads;

    for (int i = 0; i < 10; ++i) {
        threads.emplace_back(foo, 100);
    }

    for (auto &t : threads) {
        t.join();
    }

    std::cout << cnt << std::endl;

    return 0;
}

