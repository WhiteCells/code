#include <thread>
#include <iostream>

std::thread createThread1() {
    return std::thread([] {
        std::cout << "thread" << std::endl;
    });
}

std::thread createThread2() {
    std::thread t([] {
        std::cout << "thread" << std::endl;
    });
    return t;
}

void processThread(std::thread t) {
    t.join();
}

int main(int argc, char *argv[]) {
    std::thread t1 = createThread1();
    t1.join();

    std::thread t2 = createThread2();
    t2.join();

    std::thread t3([] {
        std::cout << "t3" << std::endl;
    });
    processThread(std::move(t3));

    processThread(std::thread([] {
        std::cout << "t4" << std::endl;
    }));

    return 0;
}