#include "../../head_file.h"

/*
problme: 7006. 销售利润最大化
给你一个整数 n 表示数轴上的房屋数量，编号从 0 到 n - 1 。
另给你一个二维整数数组 offers ，其中 offers[i] = [starti, endi, goldi] 表示第 i 个买家想要以 goldi 枚金币的价格购买从 starti 到 endi 的所有房屋。
作为一名销售，你需要有策略地选择并销售房屋使自己的收入最大化。
返回你可以赚取的金币的最大数目。
注意 同一所房屋不能卖给不同的买家，并且允许保留一些房屋不进行出售。
输入：n = 5, offers = [[0,0,1],[0,2,2],[1,3,2]]
输出：3
解释：
有 5 所房屋，编号从 0 到 4 ，共有 3 个购买要约。
将位于 [0,0] 范围内的房屋以 1 金币的价格出售给第 1 位买家，并将位于 [1,3] 范围内的房屋以 2 金币的价格出售给第 3 位买家。
可以证明我们最多只能获得 3 枚金币。
提示：
    1 <= n <= 10^5
    1 <= offers.length <= 10^5
    offers[i].length == 3
    0 <= starti <= endi <= n - 1
    1 <= goldi <= 10^3
url: https://leetcode.cn/problems/maximize-the-profit-as-the-salesman/
@Author: Eorys
@Date: 2023-08-20 07:01:57
@Last Modified by: Eorys
@Last Modified time: 2023-08-20 07:01:57
@Description:
*/

/*
dp
1. 选与不选
2. 枚举选哪个
从后向前看，考虑 end
总共有 n 个房子 [0, 1, 2, ..., n - 1]
f(n - 1) 表示卖 0 ~ n - 1 范围房子最大收益
从后向前进行递推，选还是不选
状态转移方程
不选: f(n - 1) = f(n - 2)
选:   f(n - 1) = f(start - 1) + g

不选: f(i) = f(i - 1)           -> f(i + 1) = f(i) 防止越界访问
选:   f(i) = f(start - 1) + g   -> f(i + 1) = f(start) + g

f(i + 1) : 0 ~ i 的最大收益
 */
class Solution {
public:
    int maximizeTheProfit(int n, vector<vector<int>>& offers) {
        map<int, pair<int, int>> mp;
        for (const auto& offer : offers) {
            mp[offer[1]] = make_pair(offer[0], offer[2]);
        }
        vector<int> dp(n + 1);
        for (const auto& m : mp) {
            int start = m.second.first;
            int end = m.first;
            int gold = m.second.second;
            dp[end + 1] = dp[end];
            dp[end + 1] = max(dp[end + 1], dp[start] + gold);
        }
        return dp[n];
    }
};


int main() {
    int n = 5;
    vector<vector<int>> offers { { 0, 0, 1 }, { 0, 2, 2 }, { 1, 3, 2 } };
    Solution s;
    cout << s.maximizeTheProfit(n, offers) << '\n';
    return 0;
}