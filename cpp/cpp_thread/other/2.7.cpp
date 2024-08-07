#include <thread>
#include <iostream>

class joining_thread {
public:
    joining_thread() noexcept = default;

    template<typename Callable, typename ...Args>
    explicit joining_thread(Callable &&func, Args && ... args)
        : thread_(std::forward<Callable>(func),
        std::forward<Args>(args)...) {

    }

    explicit joining_thread(std::thread t) noexcept
        : thread_(std::move(t)) {

    }

    explicit joining_thread(joining_thread &&other) noexcept
        : thread_(std::move(other.thread_)) {

    }

    joining_thread &operator=(std::thread t) noexcept {
        if (joinable()) {
            join();
        }
        thread_ = std::move(t);
        return *this;
    }

    joining_thread &operator=(joining_thread &&other) noexcept {
        if (joinable()) {
            join();
        }
        thread_ = std::move(other.thread_);
        return *this;
    }

    ~joining_thread() {
        if (joinable()) {
            join();
        }
    }

    void swap(joining_thread &other) noexcept {
        thread_.swap(other.thread_);
    }

    std::thread::id get_id() const noexcept {
        return thread_.get_id();
    }

    bool joinable() {
        return thread_.joinable();
    }

    void join() {
        thread_.join();
    }

    void detach() {
        thread_.detach();
    }

    std::thread &as_thread() noexcept {
        return thread_;
    }

    const std::thread &as_thread() const noexcept {
        return thread_;
    }

private:
    std::thread thread_;
};

int main(int argc, char *argv[]) {
    // std::jthread my_thread([] {
    //     std::cout << "jthread" << std::endl;
    // });

    joining_thread my_thread([] {
        std::cout << "joining thread" << std::endl;
    });
    return 0;
}