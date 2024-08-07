#include <iostream>
#include <vector>

int main() {
    int N = 0;
    std::cin >> N;
    std::vector<int> A(N);
    for (int i = 0; i < N; ++i) {
        std::cin >> A[i];
    }
    std::vector<int> B{ 0 };
    for (const auto &ele : A) {
        B.emplace_back(B.back() + ele);
    }
    for (int i = 1; i < B.size(); ++i) {
        std::cout << B[i] << ' ';
    }
    std::cout << '\n';
}

// int main() {
//     int N = 0;
//     std::cin >> N;
//     std::vector<int> A(N);
//     for (int i = 0; i < N; ++i) {
//         std::cin >> A[i];
//     }
//     std::vector<int> B(N);
//     B[0] = A[0]; // 前缀和数组第 1 项 与 原数组第 1 项 相等
//     for (int i = 1; i < N; ++i) {
//         B[i] = B[i - 1] + A[i];
//     }
//     for (const auto &ele : B) {
//         std::cout << ele << ' ';
//     }
//     std::cout << '\n';
//     return 0;
// }