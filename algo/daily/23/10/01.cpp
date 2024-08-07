#include "../../head_file.h"

/*
problme: 121. 买卖股票的最佳时机

给定一个数组 prices ，它的第 i 个元素 prices[i] 表示一支给定股票第 i 天的价格。

你只能选择 某一天 买入这只股票，并选择在 未来的某一个不同的日子 卖出该股票。设计一个算法来计算你所能获取的最大利润。

返回你可以从这笔交易中获取的最大利润。如果你不能获取任何利润，返回 0 。


示例 1：

输入：[7,1,5,3,6,4]
输出：5
解释：在第 2 天（股票价格 = 1）的时候买入，在第 5 天（股票价格 = 6）的时候卖出，最大利润 = 6-1 = 5 。
     注意利润不能是 7-1 = 6, 因为卖出价格需要大于买入价格；同时，你不能在买入前卖出股票。

示例 2：

输入：prices = [7,6,4,3,1]
输出：0
解释：在这种情况下, 没有交易完成, 所以最大利润为 0。



提示：

    1 <= prices.length <= 105
    0 <= prices[i] <= 104


url:
 */

// TLE
// time complexity: O(n^2)
// spatial complexity: O(1)
class Solution1 {
public:
    int maxProfit(vector<int> &prices) {
        int res = 0, n = prices.size();
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                res = max(res, prices[j] - prices[i]);
            }
        }
        return res;
    }
};

// time complexity: O(n)
// spatial complexity: O(1)
class Solution2 {
public:
    int maxProfit(vector<int> &prices) {
        int res = 0, mn = INT_MAX, n = prices.size();
        for (int i = 0; i < n; ++i) {
            // 找最低购入价格
            if (prices[i] < mn) {
                mn = prices[i];
            }
            // 已有最低购入价格，则考虑此时卖出
            else {
                res = max(res, prices[i] - mn);
            }
        }
        return res;
    }
};

// 简化
class Solution3 {
public:
    int maxProfit(vector<int> &prices) {
        int n = prices.size();
        int mn = INT_MAX; // 最低成本购入
        int res = 0;
        for (int i = 0; i < n; ++i) {
            mn = min(prices[i], mn);
            res = max(res, prices[i] - mn);
        }
        return res;
    }
};

// time complexity: O(n)
// spatial complexity: O(n)
// 动态规划
// 只能交易 1 次
class Solution4 {
public:
    int maxProfit(vector<int> &prices) {
        
    }
};

int main() {
    vector<int> prices { 7, 1, 5, 3, 6, 4 };
    cout << Solution1().maxProfit(prices) << '\n';
    cout << Solution2().maxProfit(prices) << '\n';
    cout << Solution3().maxProfit(prices) << '\n';
    cout << Solution4().maxProfit(prices) << '\n';
    return 0;
}