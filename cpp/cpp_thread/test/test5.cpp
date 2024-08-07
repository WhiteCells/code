#include <iostream>
#include <memory>
#include <thread>

class Object {};

void foo(std::unique_ptr<Object> ptr) {}

int main(int argc, char *argv[]) {
    std::unique_ptr<Object> ptr = std::make_unique<Object>();
    std::thread my_thread(foo, std::move(ptr));
    my_thread.join();
    return 0;
}
