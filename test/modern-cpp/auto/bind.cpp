#include <iostream>
#include <functional>
#include <map>

template<typename T1, typename T2>
auto func(T1 x, T2 y) {
    return x + y;
}

int main() {
    // auto f = []() {};
    auto bound_function = std::bind([](int a) {std::cout << a << std::endl;}, 10);

    // 调用绑定的函数对象
    bound_function();

    auto f = [&](auto a, auto b) -> decltype(a + b) {
        return a + b;
    };

    std::cout << f(1.1, 2) << std::endl;

    std::cout << func(1.1, -1) << std::endl;

    std::map<std::string, int> mp;
    mp["111"] = 111;
    mp["222"] = 222;
    mp["333"] = 333;

    // for (std::map<std::string, int>::iterator it = mp.begin(); it != mp.end(); ++it) {
    for (std::map<std::string, int>::const_iterator it = mp.begin(); it != mp.end(); ++it) {
    // for (std::pair<const std::string, int> &it : mp) {
    // for (std::pair<std::string, int> &p : mp) { // compilation failed
    // for (auto &p : mp) {
        std::cout << it->first << " " << it->second << std::endl;
    }

    return 0;
}