#include <condition_variable>
#include <memory>
#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>

std::mutex mutex;
std::condition_variable cv;
std::atomic_bool odd {true};

void trunPrint() {
    std::thread t1([]() {
        for (;;) {
            std::unique_lock<std::mutex> ulock(mutex);
            cv.wait(ulock, []() {
                return odd == true;
            });
            odd = false;
            std::cout << "1" << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            cv.notify_one();
        }
    });

    std::thread t2([]() {
        for (;;) {
            std::unique_lock<std::mutex> ulock(mutex);
            cv.wait(ulock, []() {
                return odd == false;
            });
            odd = true;
            std::cout << "22222" << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            cv.notify_one();
        }
    });

    t1.join();
    t2.join();
}

int main(int argc, char *argv[]) {
    trunPrint();
    return 0;
}