#include "../../head_file.h"

/*
problme: 188. 买卖股票的最佳时机 IV

给你一个整数数组 prices 和一个整数 k ，其中 prices[i] 是某支给定的股票在第 i 天的价格。

设计一个算法来计算你所能获取的最大利润。你最多可以完成 k 笔交易。也就是说，你最多可以买 k 次，卖 k 次。

注意：你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。

示例 1：

输入：k = 2, prices = [2,4,1]
输出：2
解释：在第 1 天 (股票价格 = 2) 的时候买入，在第 2 天 (股票价格 = 4) 的时候卖出，这笔交易所能获得利润 = 4-2 = 2 。

示例 2：

输入：k = 2, prices = [3,2,6,5,0,3]
输出：7
解释：在第 2 天 (股票价格 = 2) 的时候买入，在第 3 天 (股票价格 = 6) 的时候卖出, 这笔交易所能获得利润 = 6-2 = 4 。
     随后，在第 5 天 (股票价格 = 0) 的时候买入，在第 6 天 (股票价格 = 3) 的时候卖出, 这笔交易所能获得利润 = 3-0 = 3 。

提示：

    1 <= k <= 100
    1 <= prices.length <= 1000
    0 <= prices[i] <= 1000

url: https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-iv/description/
 */

// time complexity: O()
// spatial complexity: O()
class Solution {
public:
    int maxProfit(int k, vector<int> &prices) {
        int n = prices.size();
        vector<vector<vector<int>>> menm(n, vector<vector<int>>(k + 1, vector<int>(2, -1)));
        function<int(int, int, bool)> dfs = [&](int i, int j, bool hold)->int {
            if (i < 0) {
                return hold ? INT_MIN : 0;
            }
            if (j < 0) {
                return INT_MIN;
            }
            if (-1 != menm[i][j][hold]) {
                return menm[i][j][hold];
            }
            if (hold) {
                return menm[i][j][true] = max(dfs(i - 1, j, true), dfs(i - 1, j, false) - prices[i]);
            }
            return menm[i][j][false] = max(dfs(i - 1, j, false), dfs(i - 1, j - 1, true) + prices[i]);
        };
        return dfs(n - 1, k, 0);
    }
};

int main() {
    vector<int> prices{ 3, 2, 6, 5, 0, 3 };
    int k = 2;
    cout << Solution().maxProfit(k, prices) << '\n';
    return 0;
}