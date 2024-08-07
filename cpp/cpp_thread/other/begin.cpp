#include <thread>
#include <iostream>
#include <stack>

int main(int argc, char *argv[]) {
    std::thread t1([](int i) {std::cout << "t1 hello thread" << i << std::endl;}, 1);
    std::thread t2([] {std::cout << "t2 hello thread" << std::endl;});
    t1.join();
    t2.join();
    std::thread t3;
    t3.join();

    return 0;
}