#include <thread>
#include <mutex>
#include <iostream>

std::mutex mtx1;
std::mutex mtx2;
int val1 = 0;
int val2 = 1;

void foo1() {
    for (int i = 0; i < 10; ++i) {
        std::cout << "foo1 begin" << std::endl;
        mtx1.lock();
        val1 = 100;
        mtx1.unlock();
        mtx2.lock();
        
        mtx2.unlock();
    }
}

void foo2() {

}

int main(int argc, char *argv[]) {
    
    return 0;
}