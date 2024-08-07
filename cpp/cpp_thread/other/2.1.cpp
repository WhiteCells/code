#include <thread>
#include <iostream>

struct Func {
    int &i_;
    Func(int &i) : i_(i) {}
    void operator()() {
        for (unsigned j = 0; j < 1000000; ++j) {
            std::cout << i_ << std::endl;
        }
    }
};

int main(int argc, char *argv[]) {
    int n = 0;
    Func my_func(n);
    std::thread my_thread(my_func);
    my_thread.join();
    return 0;
}