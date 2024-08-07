#include <list>
#include <iostream>
#include <thread>
#include <mutex>
#include <algorithm>

std::list<int> list;

std::mutex mtx;

void addToList(int val) {
    std::lock_guard<std::mutex> gurad(mtx);
    list.push_back(val);
}

bool findValFormList(int val) {
    std::lock_guard<std::mutex> guard(mtx);
    return std::find(list.begin(), list.end(), val) != list.end();
}

int main(int argc, char *argv[]) {
    std::thread add_to_list_thread1(addToList, 10);
    std::thread add_to_list_thread2(addToList, 20);
    add_to_list_thread1.join();
    add_to_list_thread2.join();
    std::cout << findValFormList(20) << std::endl;
    return 0;
}