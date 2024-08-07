// C++ 标准库中的前缀和函数，定义于 numeric 函数
#include <functional>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>

int main() {
    std::vector<int> v(10, 2); // v = {2, 2, 2, 2, 2, 2, 2, 2, 2, 2}

    std::cout << "前 " << v.size() << " 个偶数是：";
    // 将结果写入流 cout
    std::partial_sum(v.cbegin(), v.cend(),
                     std::ostream_iterator<int>(std::cout, " "));
    std::cout << '\n';

    // 将结果写回 vector v
    std::partial_sum(v.cbegin(), v.cend(),
                     v.begin(), std::multiplies<int>());

    std::cout << "2 的前 " << v.size() << " 个幂是：";
    for (int n : v) {
        std::cout << n << ' ';
    }
    std::cout << '\n';
    return 0;
}