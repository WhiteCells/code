#include <mutex>
#include <condition_variable>
#include <queue>
#include <memory>
#include <iostream>
#include <thread>
#include <functional> // std::ref

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
        std::unique_lock<std::mutex> ulock(mtx_);
        que_.push(value);
        que_cv_.notify_one();
    }

    void wait_pop(T &value) {
        std::unique_lock<std::mutex> ulock(mtx_);
        que_cv_.wait(ulock, [this]() {
            return !que_.empty();
        });
        value = que_.front();
        que_.pop();
    }

    void try_pop(T &value) {
        std::lock_guard<std::mutex> lock(mtx_);
        if (que_.empty()) {
            return;
        }
        value = que_.front();
        que_.pop();
    }

    std::shared_ptr<T> wait_pop() {
        std::unique_lock<std::mutex> ulock(mtx_);
        que_cv_.wait(ulock, [this]() {
            return !que_.empty();
        });
        std::shared_ptr<T> front = std::make_shared<T>(que_.front());
        que_.pop();
        return front;
    }

    std::shared_ptr<T> try_pop() {
        std::lock_guard<std::mutex> lock(mtx_);
        if (que_.empty()) {
            return nullptr;
        }
        std::shared_ptr<T> front = std::make_shared<T>(que_.front());
        que_.pop();
        return front;
    }

    bool empty() {
        std::lock_guard<std::mutex> lock(mtx_);
        return que_.empty();
    }

private:
    mutable std::mutex mtx_;
    std::condition_variable que_cv_;
    std::queue<T> que_;
};

// ThreadsafeQueue<int> que;

// void producer(ThreadsafeQueue<int> &que) {
void producer(std::shared_ptr<ThreadsafeQueue<int>> que) {
    for (int i = 0;;) {
        que->push(i);
        std::cout << "producer: " << i++ << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

// void consumer1(ThreadsafeQueue<int> &que) {
void consumer1(std::shared_ptr<ThreadsafeQueue<int>> que) {
    for (;;) {
        auto front = que->wait_pop();
        std::cout << "consumer1: " << *front << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}

// void consumer2(ThreadsafeQueue<int> &que) {
void consumer2(std::shared_ptr<ThreadsafeQueue<int>> que) {
    for (;;) {
        auto front = que->try_pop();
        if (front) {
            std::cout << "consumer2: " << *front << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}

void testProducerAndConsumer() {
    // ThreadsafeQueue<int> que;
    // std::thread producer_thread(producer, std::ref(que));
    // std::thread consumer_thread1(consumer1, std::ref(que));
    // std::thread consumer_thread2(consumer2, std::ref(que));

    // or
    std::shared_ptr<ThreadsafeQueue<int>> que = std::make_shared<ThreadsafeQueue<int>>();
    std::thread producer_thread(producer, que);
    std::thread consumer_thread1(consumer1, que);
    std::thread consumer_thread2(consumer2, que);

    producer_thread.join();
    consumer_thread1.join();
    consumer_thread2.join();
}

int main(int argc, char *argv[]) {
    testProducerAndConsumer();
    return 0;
}