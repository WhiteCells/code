#include <iostream>
#include <vector>
#include <numeric>
#include <ctime>

void test01() {
    std::vector<int> nums;
    long long sum = 0;
    for (int i = 0; i < 10; ++i) {
        long long num = rand() % static_cast<int>(1e9);
        nums.emplace_back(num);
        sum += num;
    }
    long long res = std::accumulate(nums.begin(), nums.end(), 0LL);
    std::cout << sum << std::endl;
    std::cout << res << std::endl;
}

int main() {
    std::srand(static_cast<unsigned>(time(NULL)));
    test01();
    return 0;
}