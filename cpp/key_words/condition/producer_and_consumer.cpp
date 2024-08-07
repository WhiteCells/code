#include <iostream>
#include <condition_variable>
#include <queue>
#include <thread>

class ProducerAndConsumer {
public:
    static void producer(size_t num) {
        for (size_t i = 0; i < num; ++i) {
            std::unique_lock<std::mutex> locker(mtx_);
            // 等待消费者腾出空间
            producer_cv_.wait(locker, [] { return que_.size() < max_size_; });
            que_.push(static_cast<int>(i));
            consumer_cv_.notify_one(); // 通知消费者有新数据
        }
        {
            std::unique_lock<std::mutex> locker(mtx_);
            finished_ = true;
            consumer_cv_.notify_all(); // 通知所有消费者生产完成
        }
    }

    static int i;

    static void consumer() {
        while (true) {
            std::unique_lock<std::mutex> locker(mtx_);
            consumer_cv_.wait(locker, [] { return !que_.empty() || finished_; });
            while (!que_.empty()) {
                int val = que_.front();
                que_.pop();
                locker.unlock();
                std::cout << val << std::endl;
                locker.lock();
                producer_cv_.notify_one(); // 通知生产者可以生产
            }
            if (finished_ && que_.empty()) {
                break;
            }
        }
    }

    static std::mutex mtx_;
    static std::condition_variable consumer_cv_;
    static std::condition_variable producer_cv_;
    static std::queue<int> que_;
    static const size_t max_size_ = 130;
    static bool finished_;
};

int ProducerAndConsumer::i = 0;
std::mutex ProducerAndConsumer::mtx_;
std::condition_variable ProducerAndConsumer::consumer_cv_;
std::condition_variable ProducerAndConsumer::producer_cv_;
std::queue<int> ProducerAndConsumer::que_;
bool ProducerAndConsumer::finished_ = false;

int main(int argc, char *argv[]) {
    std::thread t1(ProducerAndConsumer::producer, 100);
    std::thread t2(ProducerAndConsumer::consumer);
    std::thread t3(ProducerAndConsumer::producer, 30);
    std::thread t4(ProducerAndConsumer::consumer);

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    return 0;
}
