#include "../../head_file.h"

/*
problme: 309. 买卖股票的最佳时机含冷冻期

给定一个整数数组prices，其中第  prices[i] 表示第 i 天的股票价格 。​

设计一个算法计算出最大利润。在满足以下约束条件下，你可以尽可能地完成更多的交易（多次买卖一支股票）:

    卖出股票后，你无法在第二天买入股票 (即冷冻期为 1 天)。

注意：你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。


示例 1:

输入: prices = [1,2,3,0,2]
输出: 3
解释: 对应的交易状态为: [买入, 卖出, 冷冻期, 买入, 卖出]

示例 2:

输入: prices = [1]
输出: 0


提示：

    1 <= prices.length <= 5000
    0 <= prices[i] <= 1000

url: https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-with-cooldown/description/
 */

// time complexity: O(n)
// spatial complexity: O(n)
// 记忆化 dfs
class Solution1 {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        vector<vector<int>> menm(n, vector<int>(2, -1));
        function<int(int, bool)> dfs = [&](int i, bool hold)->int {
            if (i < 0) {
                return hold ? INT_MIN : 0;
            }
            if (-1 != menm[i][hold]) {
                return menm[i][hold];
            }
            if (hold) {
                return menm[i][true] = max(dfs(i - 1, true), dfs(i - 2, false) - prices[i]);
            }
            return menm[i][false] = max(dfs(i - 1, false), dfs(i - 1, true) + prices[i]);
        };
        return dfs(n - 1, 0);
    }
};

// time complexity: O()
// spatial complexity: O()
// 动态规划
class Solution2 {
public:
    int maxProfit(vector<int> &prices) {
        int n = prices.size();
        vector<vector<int>> dp(n + 2, vector<int>(2, 0));
        dp[1][1] = INT_MIN;
        for (int i = 0; i < n; ++i) {
            dp[i + 2][0] = max(dp[i + 1][0], dp[i + 1][1] + prices[i]);
            dp[i + 2][1] = max(dp[i + 1][1], dp[i][0] - prices[i]);
        }
        return dp[n][0];
    }
};

int main() {
    vector<int> prices { 1, 2, 3, 0, 2 };
    cout << Solution1().maxProfit(prices) << '\n';
    cout << Solution2().maxProfit(prices) << '\n';
    return 0;
}