#include <future>
#include <thread>
#include <iostream>
#include <functional>

int main(int argc, char *argv[]) {
    std::packaged_task<int()> task(std::bind([](int num) -> int {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        std::cout << "task ..." << std::endl;
        return num + 10;
    }, 20));
    std::future<int> res = task.get_future();
    std::thread(std::move(task)).detach();
    std::cout << "main ..." << std::endl;
    int ret = res.get();
    std::cout << "ret: " << ret << std::endl;
    return 0;
}