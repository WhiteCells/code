#include "D:/distake/Coding/head_file.h"

/*
 * @Author: WhiteCells
 * @Date: 2023-05-19 21:51:32
 * @Last Modified by: WhiteCells
 * @Last Modified time: 2023-05-19 21:51:32
 * @Description: 122.买卖股票的最佳时机
 * https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-ii/
*/

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int res = 0;
        for (int i = 0; i + 1 < prices.size(); ++i) {
            int cnt = prices[i + 1] - prices[i]; // 利润可以转化为连续数之间的差值之和
            if (cnt > 0) { // 利润大于 0，继续加利润
                res += cnt;
            }
            // else { // 利润小于 0，结束本次利润统计
            //     cnt = 0;
            // }
        }
        return res;
    }
};


int main() {
    Solution s;
    // vector<int> prices {7, 1, 5, 3, 6, 4};
    vector<int> prices {1, 2, 3, 4, 5};
    cout << s.maxProfit(prices);
    return 0;
}