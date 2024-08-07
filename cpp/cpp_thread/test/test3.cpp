#include <thread>
#include <iostream>

class X {
public:
    void foo() { std::cout << "foo" << std::endl; }
};

struct Y {
    void foo() { std::cout << "foo" << std::endl; }
};

int main(int argc, char *argv[]) {
    X x;
    std::thread my_thread(&X::foo, &x);
    my_thread.join();

    Y y;
    // std::thread my_thread2(&Y::foo, &y);
    std::thread my_thread2(&Y::foo, &y);
    my_thread2.join();
    return 0;
}