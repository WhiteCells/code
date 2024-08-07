#include "../../head_file.h"

/*
problme: 122. 买卖股票的最佳时机 II

给你一个整数数组 prices ，其中 prices[i] 表示某支股票第 i 天的价格。

在每一天，你可以决定是否购买和/或出售股票。你在任何时候 最多 只能持有 一股 股票。你也可以先购买，然后在 同一天 出售。

返回 你能获得的 最大 利润 。

示例 1：

输入：prices = [7,1,5,3,6,4]
输出：7
解释：在第 2 天（股票价格 = 1）的时候买入，在第 3 天（股票价格 = 5）的时候卖出, 这笔交易所能获得利润 = 5 - 1 = 4 。
     随后，在第 4 天（股票价格 = 3）的时候买入，在第 5 天（股票价格 = 6）的时候卖出, 这笔交易所能获得利润 = 6 - 3 = 3 。
     总利润为 4 + 3 = 7 。

示例 2：

输入：prices = [1,2,3,4,5]
输出：4
解释：在第 1 天（股票价格 = 1）的时候买入，在第 5 天 （股票价格 = 5）的时候卖出, 这笔交易所能获得利润 = 5 - 1 = 4 。
     总利润为 4 。

示例 3：

输入：prices = [7,6,4,3,1]
输出：0
解释：在这种情况下, 交易无法获得正利润，所以不参与交易可以获得最大利润，最大利润为 0 。

提示：

    1 <= prices.length <= 3 * 104
    0 <= prices[i] <= 104

url: https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-ii/description/
 */

// time complexity: O(n)
// spatial complexity: O(1)
// 贪心
// 1 3 7 最大利润: (7-1) = (3-1)+(7-3)
class Solution1 {
public:
    int maxProfit(vector<int> &prices) {
        int res = 0, n = prices.size();
        for (int i = 0; i + 1 < n; ++i) {
            int profit = prices[i + 1] - prices[i];
            if (profit > 0) {
                res += profit;
            }
        }
        return res;
    }
};

// time complexity: O(n)
// spatial complexity: O(n)
// 记忆化 dfs
// 定义 dfs(i, 0) 表示到 i 天结束时，未持有股票的最大利润
// 定义 dfs(i, 1) 表示到 i 天结束时，持有股票的最大利润
// 当前的利润 dfs(i, hold) 有三种情况
// 1. 什么不做 dfs(i - 1, hold)
// 2. 买入股票 dfs(i - 1, !hold) - prices[i]
// 3. 卖出股票 dfs(i - 1, hold) + prices[i]
class Solution2 {
public:
    int maxProfit(vector<int> &prices) {
        int n = prices.size();
        menm.resize(n, vector<int>(2, -1));
        return dfs(n - 1, false, prices); // max(dfs(n - 1, 0), dfs(n - 1, 1)) 最后一天一定不能持有股票
    }
private:
    vector<vector<int>> menm; // 用于记忆化搜索
    int dfs(int i, bool hold, vector<int> &prices) {
        if (i < 0) {
            return hold ? INT_MIN : 0;
        }
        if (-1 != menm[i][hold]) {
            return menm[i][hold];
        }
        if (hold) {
            return menm[i][hold] = max(dfs(i - 1, true, prices), dfs(i - 1, false, prices) - prices[i]);
        }
        return menm[i][hold] = max(dfs(i - 1, false, prices), dfs(i - 1, true, prices) + prices[i]);
    }
};

// 使用 lambda 简化
class Solution3 {
public:
    int maxProfit(vector<int> &prices) {
        int n = prices.size();
        vector<vector<int>> menm(n, vector<int>(2, -1));
        function<int(int, bool)> dfs = [&](int i, bool hold)->int {
            if (i < 0) {
                return hold ? INT_MIN : 0;
            }
            if (-1 != menm[i][hold]) { // 当前结果之前出现过，则直接跳出当前递归
                return menm[i][hold];
            }
            if (hold) {
                return menm[i][hold] = max(dfs(i - 1, true), dfs(i - 1, false) - prices[i]);
            }
            return menm[i][hold] = max(dfs(i - 1, false), dfs(i - 1, true) + prices[i]);
        };
        return dfs(n - 1, false); // max(dfs(n - 1, false), dfs(n - 1, true)) 最后一天一定不能持有股票
    }
};

// time complexity: O(n)
// spatial complexity: O(n)
// 动态规划
class Solution4 {
public:
    int maxProfit(vector<int> &prices) {
        int n = prices.size();
        vector<vector<int>> dp(n + 1, vector<int>(2, 0));
        dp[0][1] = INT_MIN;
        for (int i = 0; i < n; ++i) {
            dp[i + 1][0] = max(dp[i][0], dp[i][1] + prices[i]);
            dp[i + 1][1] = max(dp[i][1], dp[i][0] - prices[i]);
        }
        return dp[n][0];
    }
};

// 优化空间
// time complexity: O(n)
// spatial complexity: O(1)
class Solution5 {
public:
    int maxProfit(vector<int> &prices) {
        int n = prices.size(), dp0 = 0, dp1 = INT_MIN;
        for (int i = 0; i < n; ++i) {
            int tmp = max(dp0, dp1 + prices[i]);
            dp1 = max(dp1, dp0 - prices[i]);
            dp0 = tmp;
        }
        return dp0;
    }
};


int main() {
    vector<int> prices { 7, 1, 5, 3, 6, 4 };
    cout << Solution1().maxProfit(prices) << '\n';
    cout << Solution2().maxProfit(prices) << '\n';
    cout << Solution3().maxProfit(prices) << '\n';
    cout << Solution4().maxProfit(prices) << '\n';
    cout << Solution5().maxProfit(prices) << '\n';
    return 0;
}