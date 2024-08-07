#include "../../head_file.h"

/*
 * @Author: WhiteCells
 * @Date: 2023-06-03 12:39:11
 * @Last Modified by: WhiteCells
 * @Last Modified time: 2023-06-03 12:39:11
 * @Description: 746. 使用最小花费爬楼梯
 * https://leetcode.cn/problems/min-cost-climbing-stairs/
*/

class Solution {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        int dp0 = 0; // 你可以选择从下标为 0 或下标为 1 的台阶开始爬楼梯。
        int dp1 = 0; // 所以到 0、1 位置上就不需要消耗体力
        for (int i = 2; i <= cost.size(); ++i) {
            // 前两个位置都可以到当前位置
            // 前两个值中去找一个需要最小的体力值
            int dp2 = min(dp0 + cost[i - 2], dp1 + cost[i - 1]);
            dp0 = dp1;
            dp1 = dp2;
        }
        return dp1;
    }
};

class Solution2 {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        vector<int> dp(cost.size() + 1);
        dp[0] = 0, dp[1] = 0;
        for (int i = 2; i <= cost.size(); ++i) {
            dp[i] = min(dp[i - 2] + cost[i - 2], dp[i - 1] + cost[i - 1]);
        }
        return dp[cost.size()];
    }
};


int main() {
    Solution s;
    vector<int> cost {10, 15, 20};
    cout << s.minCostClimbingStairs(cost) << endl;

    Solution2 s2;
    // vector<int> cost2 {10, 15, 20};
    vector<int> cost2 {1, 100, 1, 1, 1, 100, 1, 1, 100, 1};
    cout << s2.minCostClimbingStairs(cost2) << endl;
    return 0;
}