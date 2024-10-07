#include <queue>
#include <mutex>
#include <condition_variable>
#include <memory>
#include <thread>
#include <iostream>

template<typename T>
class ThreadsafeQueue {
public:
    ThreadsafeQueue() {}
    explicit ThreadsafeQueue(const ThreadsafeQueue &other) {
        if (this == &other) {
            return;
        }
        que_ = other.que_;
    }
    ~ThreadsafeQueue() {}

    void push(T value) {
        std::lock_guard<std::mutex> lock(que_mtx_);
        que_.push(value);
        que_cv_.notify_one();
    }

    void wait_pop(T &value) {
        std::unique_lock<std::mutex> ulock(que_mtx_);
        que_cv_.wait(ulock, [this]() {
            return !que_.empty();
        });
        value = que_.front();
        que_.pop();
    }

    void try_pop(T &value) {
        std::lock_guard<std::mutex> lock(que_mtx_);
        if (que_.empty()) {
            return;
        }
        value = que_.front();
        que_.pop();
    }

    std::shared_ptr<T> wait_pop() {
        std::unique_lock<std::mutex> ulock(que_mtx_);
        que_cv_.wait(ulock, [this]() {
            return !que_.empty();
        });
        std::shared_ptr<T> front = std::make_shared<T>(que_.front());
        que_.pop();
        return front;
    }

    std::shared_ptr<T> try_pop() {
        std::lock_guard<std::mutex> lock(que_mtx_);
        if (que_.empty()) {
            return nullptr;
        }
        std::shared_ptr<T> front = std::make_shared<T>(que_.front());
        que_.pop();
        return front;
    }

private:
    std::mutex que_mtx_;
    std::condition_variable que_cv_;
    std::queue<T> que_;
};

void producer(ThreadsafeQueue<int> &que) {
    for (int i = 0;;) {
        que.push(i);
        std::cout << "producer: " << i++ << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void consumer1(ThreadsafeQueue<int> &que) {
    for (;;) {
        auto front = que.wait_pop();
        std::cout << "consumer1: " << *front << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}

void consumer2(ThreadsafeQueue<int> &que) {
    for (;;) {
        auto front = que.try_pop();
        if (front) {
            std::cout << "consumer2: " << *front << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}

void testProducerAndConsumer() {
    ThreadsafeQueue<int> que;
    std::thread producer_thread(producer, std::ref(que));
    std::thread consumer1_thread(consumer1, std::ref(que));
    std::thread consumer2_thread(consumer2, std::ref(que));

    producer_thread.join();
    consumer1_thread.join();
    consumer2_thread.join();
}

int main(int argc, char *argv[]) {
    testProducerAndConsumer();
    return 0;
}