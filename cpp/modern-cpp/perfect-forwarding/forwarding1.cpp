#include <iostream>
#include <string>
#include <chrono>

template<class T>
void showType(T t) {
    // std::cout << typeid(t).name() << std::endl;
}

std::string getString() {
    return "hello world";
}

template<class T>
void normalForwarding(T t) {
    showType(t);
}

int main(int argc, char const *argv[]) {
    std::string str = "hello world";
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 100000000; ++i) {
        normalForwarding(str);
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;
    std::cout << "time: " << diff.count() << std::endl;
    // normalForwarding(str);
    // normalForwarding(getString());
    return 0;
}