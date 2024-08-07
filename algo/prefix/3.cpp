#include <iostream>
#include <vector>
#include <ctime>

int main() {
    std::srand(time(NULL));
    int m, n;
    std::cin >> n >> m;
    std::vector<std::vector<int>> a(n, std::vector<int>(m));
    for (auto &vec : a) {
        for (auto &ele : vec) {
            ele = rand() % 2;
        }
    }
    for (const auto &v : a) {
        for (const auto &ele : v) {
            std::cout << ele << ' ';
        }
        std::cout << '\n';
    }
    std::vector<std::vector<int>> b(n, std::vector<int>(m));
    b[0][0] = a[0][0]; // 前缀和数组第一个数与原数组第一个数相等
    // 行
    for (int j = 1; j < a[0].size(); ++j) {
        b[0][j] = b[0][j - 1] + a[0][j];
    }
    // 列
    for (int i = 1; i < a.size(); ++i) {
        b[i][0] = b[i - 1][0] + a[i][0];
    }
    for (int i = 1; i < a.size(); ++i) {
        for (int j = 1; j < a[0].size(); ++j) {
            b[i][j] = b[i - 1][j] + b[i][j - 1] - b[i - 1][j - 1] + a[i][j];
        }
    }
    for (int i = 0; i < a.size(); ++i) {
        for (int j = 0; j < a[0].size(); ++j) {
            std::cout << b[i][j] << ' ';
        }
        std::cout << '\n';
    }
    return 0;
}