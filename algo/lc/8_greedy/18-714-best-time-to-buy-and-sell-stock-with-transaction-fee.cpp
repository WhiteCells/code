#include "D:/distake/Coding/head_file.h"

/*
 * @Author: WhiteCells
 * @Date: 2023-05-30 22:49:30
 * @Last Modified by: WhiteCells
 * @Last Modified time: 2023-05-30 22:49:30
 * @Description: 714. 买卖股票的最佳时机含手续费
 * https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-with-transaction-fee/
*/

class Solution {
public:
    int maxProfit(vector<int>& prices, int fee) {
        int res = 0;
        int sum = 0;
        for (int i = 0; i < prices.size(); ++i) {
            int cnt = prices[i + 1] - prices[i];

        }
        return sum;
    }
};


int main() {
    Solution s;
    vector<int> prices { 1, 3, 2, 8, 4, 9 };
    int fee = 2;
    cout << s.maxProfit(prices, fee);
    return 0;
}

