#include <thread>
#include <iostream>

void foo1() { std::cout << "foo1" << std::endl; }
void foo2() { std::cout << "foo2" << std::endl; }

int main(int argc, char *argv[]) {
    // t1 与运行 foo1 的线程关联
    std::thread t1(foo1);

    // t1 归属权移交给 t2
    std::thread t2 = std::move(t1);

    // t1 与运行 foo2 的线程关联
    t1 = std::thread(foo2);

    std::thread t3;
    // t2 归属权移交 t3
    t3 = std::move(t2);

    // t3 的归属权移交 t1
    // 但 t1 已关联运行 foo2 的线程
    // t1 = std::move(t3);
    
    t1.join();
    t3.join();
    return 0;
}