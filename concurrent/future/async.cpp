#include <future>
#include <iostream>
#include <thread>

int task(int num) {
    std::cout << "task " << num << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    return num + 10;
}

int main(int argc, char *argv[]) {
    std::future<int> task1_res = std::async(std::launch::async, task, 1);
    std::future<int> task2_res = std::async(std::launch::deferred, task, 2);
    std::future<int> task3_res = std::async(std::launch::async | std::launch::deferred, task, 3);
    std::future<int> task4_res = std::async(task, 4);

    std::cout << "task2 res: " << task2_res.get() << std::endl << std::endl;
    std::cout << "task1 res: " << task1_res.get() << std::endl << std::endl;
    std::cout << "task3 res: " << task3_res.get() << std::endl << std::endl;
    std::cout << "task4 res: " << task4_res.get() << std::endl << std::endl;
    return 0;
}