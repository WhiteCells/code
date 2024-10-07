#include <future>
#include <thread>
#include <iostream>

int main(int argc, char *argv[]) {
    std::promise<int> prom;
    std::shared_future<int> res = prom.get_future();
    
    std::thread t1([](std::promise<int> prom) {
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        prom.set_value(10);
    }, std::move(prom));

    std::thread t2([](std::shared_future<int> res) {
        std::cout << "thread2 ..." << std::endl;
        int num = res.get() + 1000;
        std::cout << "thread2: " << num << std::endl;
    }, res);

    std::thread t3([](std::shared_future<int> res) {
        std::cout << "thread3 ..." << std::endl;
        int num = res.get() - 1020;
        std::cout << "thread3: " << num << std::endl;
    }, res);

    t1.join();
    t2.join();
    t3.join();
    return 0;
}