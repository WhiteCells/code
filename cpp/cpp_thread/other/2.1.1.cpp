#include <thread>
#include <iostream>

class Task {
public:
    void operator()() {
        std::cout << "task" << std::endl;
    }
};

void fun() {
    std::cout << "fun" << std::endl;
}

int main(int argc, char *argv[]) {
    Task task;
    std::thread my_thread(task);
    // std::thread my_thread(task());
    my_thread.join();

    std::thread my_thread2(fun);
    my_thread2.join();
    return 0;
}