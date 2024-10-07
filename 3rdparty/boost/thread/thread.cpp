#include <boost/thread/thread.hpp>
#include <boost/beast/http.hpp>
#include <iostream>
#include <cstdlib>

volatile bool flag = true;

void foo1() {
    static int cnt = 0;
    while (flag) {
        std::cout << "foo1 " << ++cnt << std::endl;
        sleep(1);
    }
}

void foo2() {
    static int cnt = 0;
    while (flag) {
        std::cout << "foo2 " << ++cnt << std::endl;
        sleep(1);
    }
}

// g++ thread.cpp -g -lboost_thread -o thread
int main() {
    boost::thread thread1(&foo1);
    boost::thread thread2(&foo2);

    system("read");
    flag = false;

    thread1.join();
    thread2.join();
    return 0;
}