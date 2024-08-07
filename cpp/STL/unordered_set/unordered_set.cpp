#include <iostream>
#include <vector>

#include <unordered_set>

void UsedSet() {
    // auto hash = [&](const std::pair<int, int>& p) {
    //     return p.first ^ p.first;
    // };
    // std::unordered_set<std::pair<int, int>, decltype(hash)> s(hash);

    struct Hash {
        size_t operator()(const std::pair<int, int>& p) const {
            return p.first ^ p.second;
        }
    };
    std::unordered_set<std::pair<int, int>, Hash> s(Hash);

}

void InitSet() {
    std::vector<int> v { 1, 2, 4, 1, 3 };
    std::unordered_set<int> s(v.begin(), v.end());
    for (const auto& ele : s) {
        std::cout << ele << ' ';
    }
    std::cout << '\n';
    std::cout << s.count(3) << '\n';
    std::cout << s.count(4) << '\n';
    std::cout << s.count(5) << '\n';
}

int main() {
    InitSet();
    return 0;
}