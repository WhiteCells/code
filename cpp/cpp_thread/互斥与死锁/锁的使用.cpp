#include <mutex>
#include <thread>
#include <iostream>

std::mutex mtx;
unsigned val = 0;

void foo() {
    for (int i = 0; i < 10; ++i) {
        mtx.lock();
        ++val;
        std::cout << "current thread id: " << std::this_thread::get_id() << std::endl;
        std::cout << "shared data val: " << val << std::endl;
        mtx.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

int main(int argc, char *argv[]) {
    std::thread t1(foo);
    std::thread t2(foo);

    t1.join();
    t2.join();
    return 0;
}