#include <iostream>
#include <vector>

#include <unordered_map>


/*
使用哈希表去重 (1, 0),(0, 1) (x, y) (y, x)
将 x, y 映射到 x * n + y

 */
void UnorderedMap() {
    std::vector<std::vector<int>> edges {
        { 1, 0 },
        { 0, 1 },
        { -1, 0 },
        { 0, -1 },
        { 1000, 200 },
        { 200, 1000 },
    };
    int n = edges.size();
    std::unordered_map<int, int> m;
    for (const auto& edge : edges) {
        int x = edge[0], y = edge[1];
        if (x > y) {
            std::swap(x, y);
        }
        ++m[x * n + y];
    }
    for (const auto& ele : m) {
        std::cout << ele.first << " " << ele.second << '\n';
    }
}

void ErgodicUnorderedMap() {
    std::unordered_map<int, std::vector<int>> mp;
    mp[4] = { 4, 5, 6 };
    mp[6] = { 6, 7, 8 };
    mp[8] = { 8, 9, 1 };
    for (const auto& v : mp) {
        for (const auto& ele : v.second) {
            std::cout << ele << ' ';
        }
        std::cout << '\n';
    }
    std::cout << mp.count(6) << '\n';
    std::cout << mp.count(7) << '\n';
}

/* [key] 访问时，如果 key 不存在，则会插入 [key] = 0 */
void Func() {
    std::unordered_map<int, int> mp;
    mp[0];
    std::cout << mp.count(0) << '\n';
    std::cout << mp.count(1) << '\n';
}

int main() {
    // UnorderedMap();
    // ErgodicUnorderedMap();
    Func();
    return 0;
}