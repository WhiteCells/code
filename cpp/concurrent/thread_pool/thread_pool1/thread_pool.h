#ifndef _THREAD_POOL_H_
#define _THREAD_POOL_H_

#include <thread>
#include <mutex>
#include <memory>
#include <condition_variable>
#include <queue>
#include <functional>
#include <future>

class ThreadPool {
public:
    explicit ThreadPool(std::size_t = std::thread::hardware_concurrency());
    ThreadPool(const ThreadPool &) = delete;
    ThreadPool &operator=(const ThreadPool &) = delete;
    ~ThreadPool();

    template<class F, class... Args>
    auto addTask(F &&f, Args&&... args)
        -> std::future<std::result_of_t<F(Args...)>>;

private:
    std::vector<std::thread> workers_;
    std::queue<std::function<void()>> tasks_;

    std::mutex que_mtx_;
    std::condition_variable condition_;
    std::atomic_bool stop_;
};

template<typename F, typename... Args>
inline auto ThreadPool::addTask(F &&f, Args&&... args)
-> std::future<std::result_of_t<F(Args...)>> {
    using return_type = std::result_of_t<F(Args...)>;

    auto task = std::make_shared<std::packaged_task<return_type()>>(
        std::bind(std::forward<F>(f), std::forward<Args>(args)...)
    );

    std::future<return_type> res = task->get_future();

    std::unique_lock<std::mutex> ulock(que_mtx_);
    if (stop_) {
        throw std::runtime_error("push stopped");
    }
    tasks_.emplace([task]() {
        (*task)();
    });
    ulock.unlock();

    condition_.notify_one();
    return res;
}

inline ThreadPool::ThreadPool(std::size_t thread_num) : stop_(false) {
    for (std::size_t i = 0; i < thread_num; ++i) {
        workers_.emplace_back([this] {
            while (true) {
                std::function<void()> task;
                std::unique_lock<std::mutex> ulock(que_mtx_);
                condition_.wait(ulock, [this] {
                    return stop_ || !tasks_.empty();
                });
                if (stop_ && tasks_.empty()) {
                    return;
                }
                task = std::move(tasks_.front());
                tasks_.pop();
                ulock.unlock();
                task();
            }
        });
    }
}

inline ThreadPool::~ThreadPool() {
    std::unique_lock<std::mutex> ulock(que_mtx_);
    stop_ = true;
    ulock.unlock();
    condition_.notify_all();
    for (auto &worker : workers_) {
        worker.join();
    }
}

#endif // _THREAD_POOL_H_