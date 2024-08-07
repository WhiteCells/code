#include <thread>
#include <iostream>
#include <hashtable.h>

void foo() {
    std::cout << "foo" << std::endl;
}

int main(int argc, char *argv[]) {
    std::thread my_thread([] {
        foo();
    });
    std::thread::id sub_thread_id = my_thread.get_id();
    my_thread.join();
    std::thread::id main_thread_id = std::this_thread::get_id();

    std::cout << "sub  thread id: " << sub_thread_id << std::endl;
    std::cout << "main thread id: " << main_thread_id << std::endl;

    return 0;
}