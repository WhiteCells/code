#include <iostream>
#include <string>
#include <future>

int main(int argc, char *argv[]) {
    std::string x = "x";

    auto future1 = std::async(std::launch::async, [&x]() {
        x = "y";
    });
    auto future2 = std::async(std::launch::async, [&x]() {
        x = "z";
    });

    future1.get();
    future2.get();

    std::cout << x;
    return 0;
}