#include <thread>
#include <iostream>
#include <exception>

struct Func {
    int &i_;
    Func(int &i) : i_(i) {}
    void operator()() {
        for (unsigned j = 0; j < 1000; ++j) {
            std::cout << i_ << std::endl;
        }
    }
};

struct A : public std::exception {
    const char *what() const throw() {
        throw "exception";
    }
};

int main(int argc, char *argv[]) {
    int n = 0;
    Func my_func(n);
    std::thread my_thread(my_func);
    try {
        // ...
        throw A();
    } catch (const A &a) {
        my_thread.join();
        std::cout << a.what() << std::endl;
        throw;
    }
    my_thread.join();
    return 0;
}