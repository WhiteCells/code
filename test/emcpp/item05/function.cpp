#include <functional>
#include <iostream>
#include <memory>
#include <vector>
#include <unordered_map>
#include <string>
#include <list>

template<class T>
class TD;

void foo1() {
    std::function<bool(const std::vector<int> &p1,
                       const std::vector<int> &p2)> func = [](const std::vector<int> &p1,
                                                              const std::vector<int> &p2) {
        return p1[0] < p2[0];
    };
}

void foo2() {
    auto func = [](const auto &p1, const auto &p2) {
        return p1[0] < p2[0];
    };
    std::cout << func(std::vector<int>{ 1, 2, 3 }, std::vector<int>{ 2, 3, 4 }) << std::endl;
    std::vector<int> v1 { 1, 2, 3 }, v2 { 2, 3, 4 };
    std::cout << func(v1, v2) << std::endl;
}

void foo3() {
    std::unordered_map<std::string, int> m;
    m.emplace("1", 1);

    for (const std::pair<std::string, int> &p : m) {
        std::cout << p.first << ' ' << p.second << std::endl;
    }

    for (const auto &p : m) {
        std::cout << p.first << ' ' << p.second << std::endl;
    }

    for (const auto p : m) {
        std::cout << p.first << ' ' << p.second << std::endl;
        // p.second = 2;
    }

    for (auto &p : m) {
        
        p.second = 2;
    }
}

int main() {
    // foo1();
    foo2();
    // foo3();
    return 0;
}
