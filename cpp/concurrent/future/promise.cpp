#include <future>
#include <thread>
#include <iostream>

void useSetValue() {
    std::promise<int> prom;
    std::future<int> res = prom.get_future();
    // std::thread([](std::promise<int> prom) {
    //     std::this_thread::sleep_for(std::chrono::milliseconds(500));
    //     prom.set_value(100);
    //     std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    //     std::cout << "sub ..." << std::endl;
    // }, std::move(prom)).detach(); // note

    std::thread t {[](std::promise<int> prom) {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        prom.set_value(100);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        std::cout << "sub ..." << std::endl;
    }, std::move(prom)};
    std::cout << "waiting for the thread to set the value ..." << std::endl;
    std::cout << "value: " << res.get() << std::endl;
    t.join();
}

void useSetException() {
    std::promise<int> prom;
    std::future<int> res = prom.get_future();
    std::thread t {[](std::promise<int> prom) {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        try {
            throw std::runtime_error("an error occurred");
        } catch (const std::exception &exp) {
            prom.set_exception(std::current_exception());
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        std::cout << "sub ..." << std::endl;
    }, std::move(prom)};

    try {
        std::cout << "waiting for the thread to set the value ..." << std::endl;
        res.get();
    } catch (const std::exception &exp) {
        std::cout << "exception what: " << exp.what() << std::endl;
    }
    t.join();
}

int main(int argc, char *argv[]) {
    useSetValue();
    std::cout << "\n\n";
    useSetException();
    return 0;
}