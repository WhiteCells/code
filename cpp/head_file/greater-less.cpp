#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

#include <functional> // 包含 greater less

void UseGreater() {
    // std::priority_queue<int> q; // 大顶堆
    // std::priority_queue<int, std::vector<int>, std::greater<int>> q; // 升序队列，小顶堆
    std::priority_queue<int, std::vector<int>, std::less<int>> q; // 降序队列，大顶堆

    std::vector<int> v{ 4, 3, 5, 2, 1 };
    // std::sort(v.begin(), v.end(), std::greater<int>()); // >  5 4 3 2 1
    std::sort(v.begin(), v.end(), std::less<int>());    // <  1 2 3 4 5
    for (auto& val : v) {
        std::cout << val << ' ';
    }
    std::cout << '\n';
}

int main() {
    UseGreater();
    return 0;
}