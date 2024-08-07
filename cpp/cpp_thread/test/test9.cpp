#include <thread>
#include <iostream>

class Task {
public:
    void operator()(int) {
        std::cout << "task" << std::endl;
    }
};

int main(int argc, char *argv[]) {
    std::thread my_thread(Task(), 1);
    my_thread.join();
    return 0;
}