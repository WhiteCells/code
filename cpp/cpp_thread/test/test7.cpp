#include <thread>
#include <iostream>

std::thread::id main_thread;

void foo() {
    std::cout << "foo: main: " <<  main_thread << std::endl;
    std::cout << "foo: sub: " << std::this_thread::get_id() << std::endl;
    if (std::this_thread::get_id() == main_thread) {
        std::cout << "==" << std::endl;
    } else {
        std::cout << "!=" << std::endl;
    }
}

int main(int argc, char *argv[]) {
    main_thread = std::this_thread::get_id();
    std::cout << main_thread << std::endl;
    std::thread my_thread(foo);
    my_thread.join();
    return 0;
}