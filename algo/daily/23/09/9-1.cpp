#include "../../head_file.h"

/*
problme: 2240. 买钢笔和铅笔的方案数
给你一个整数 total ，表示你拥有的总钱数。同时给你两个整数 cost1 和 cost2 ，分别表示一支钢笔和一支铅笔的价格。你可以花费你部分或者全部的钱，去买任意数目的两种笔。

请你返回购买钢笔和铅笔的 不同方案数目 。
输入：total = 20, cost1 = 10, cost2 = 5
输出：9
解释：一支钢笔的价格为 10 ，一支铅笔的价格为 5 。
- 如果你买 0 支钢笔，那么你可以买 0 ，1 ，2 ，3 或者 4 支铅笔。
- 如果你买 1 支钢笔，那么你可以买 0 ，1 或者 2 支铅笔。
- 如果你买 2 支钢笔，那么你没法买任何铅笔。
所以买钢笔和铅笔的总方案数为 5 + 3 + 1 = 9 种。

提示：

    1 <= total, cost1, cost2 <= 106

url: https://leetcode.cn/problems/number-of-ways-to-buy-pens-and-pencils/
*/

class Solution {
public:
    long long waysToBuyPensPencils(int total, int cost1, int cost2) {
        long long res = 0;
        for (int i = 0; i * cost1 <= total; ++i) {
            int then = total - cost1 * i; // 剩余的前全部买铅笔
            res += then / cost2 + 1;
        }
        return res;
    }
};

int main() {
    // cout << Solution().waysToBuyPensPencils(20, 10, 5) << '\n';
    cout << Solution().waysToBuyPensPencils(100, 1, 1) << '\n';
    return 0;
}