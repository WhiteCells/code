#include <thread>
#include <iostream>

class ScopedThread {
public:
    explicit ScopedThread(std::thread t)
        : thread_(std::move(t)) {
        if (!thread_.joinable()) {
            throw std::logic_error("no thread");
        }
    }

    ~ScopedThread() {
        thread_.join();
    }

    ScopedThread(const ScopedThread &) = delete;
    ScopedThread &operator=(const ScopedThread &) = delete;

private:
    std::thread thread_;
};

int main(int argc, char *argv[]) {
    ScopedThread scoped_thread(std::thread([] {
        std::cout << "scoped thread" << std::endl;
    }));
    return 0;
}