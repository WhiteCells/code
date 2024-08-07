#include <iostream>
#include <functional>

int main(int argc, char *argv[]) {
    int a = 1, b = 2;
    // std::function<int()> foo = [=]() { return a + b; };
    auto foo = [=]() { return a + b; };
    int res = foo();
    return 0;
}