#include <future>
#include <thread>
#include <iostream>

int main(int argc, char *argv[]) {
    std::future<int> res = std::async(std::launch::async, [](int num) -> int {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        return num + 10;
    }, 10);
    if (res.wait_for(std::chrono::milliseconds(499)) == std::future_status::ready) {
        std::cout << "499ms" << std::endl;
        int ret = res.get();
        std::cout << "ret: " << ret << std::endl;
    } if (res.wait_for(std::chrono::milliseconds(500)) == std::future_status::ready) {
        std::cout << "500ms" << std::endl;
        int ret = res.get();
        std::cout << "ret: " << ret << std::endl;
    } else {
        std::cout << "not ready" << std::endl;
    }
    return 0;
}