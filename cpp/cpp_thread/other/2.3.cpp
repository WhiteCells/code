#include <thread>
#include <iostream>

class ThreadGuard {
public:
    explicit ThreadGuard(std::thread &thread)
        : thread_(thread) {}

    ~ThreadGuard() {
        if (thread_.joinable()) {
            thread_.join();
        }
    }

    ThreadGuard(const ThreadGuard &) = delete;
    ThreadGuard &operator=(const ThreadGuard &) = delete;

private:
    std::thread &thread_;
};

struct Func {
    int &i_;
    Func(int &i) : i_(i) {}
    void operator()() {
        for (unsigned j = 0; j < 1000000; ++j) {
            std::cout << i_ << std::endl;
        }
    }
};


int main(int argc, char *argv[]) {
    int n = 0;
    Func my_func(n);
    std::thread my_thread(my_func);
    ThreadGuard thread_guard(my_thread);
    // 当前线程执行其他操作
    return 0;
}