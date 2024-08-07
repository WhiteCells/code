#include "../../head_file.h"

/*
problme: 1388. 3n 块披萨
给你一个披萨，它由 3n 块不同大小的部分组成，现在你和你的朋友们需要按照如下规则来分披萨：

    你挑选 任意 一块披萨。
    Alice 将会挑选你所选择的披萨逆时针方向的下一块披萨。
    Bob 将会挑选你所选择的披萨顺时针方向的下一块披萨。
    重复上述过程直到没有披萨剩下。

每一块披萨的大小按顺时针方向由循环数组 slices 表示。
输入：slices = [1,2,3,4,5,6]
输出：10
解释：选择大小为 4 的披萨，Alice 和 Bob 分别挑选大小为 3 和 5 的披萨。然后你选择大小为 6 的披萨，Alice 和 Bob 分别挑选大小为 2 和 1 的披萨。你获得的披萨总大小为 4 + 6 = 10 。
请你返回你可以获得的披萨大小总和的最大值。
提示：
    1 <= slices.length <= 500
    slices.length % 3 == 0
    1 <= slices[i] <= 1000

url: https://leetcode.cn/problems/pizza-with-3n-slices/
@Author: Eorys
@Date: 2023-08-18 06:12:48
@Last Modified by: Eorys
@Last Modified time: 2023-08-18 06:12:48
@Description:
*/

class Solution {
public:
    int maxSizeSlices(vector<int> &slices) {
        const int n = slices.size(), k = n / 3;
        vector<vector<int>> dp(n, vector<int>(k + 1, 0));
        auto f = [&](int flag) {
            dp[0][1] = slices[0 + flag];
            dp[1][1] = max(slices[0 + flag], slices[1 + flag]);
            for (int i = 2; i < n - 1; ++i) {
                for (int j = 1; j <= (i + 2) / 2 && j <= k; ++j) {
                    dp[i][j] = max(dp[i - 1][j], dp[i - 2][j - 1] + slices[i + flag]);
                }
            }
            return dp[n - 2][k];
        };
        return max(f(0), f(1));
    }
};

int main() {
    vector<int> slices { 1, 2, 3, 4, 5, 6 };
    Solution s;
    for (int i = 0; i < s)
    return 0;
}