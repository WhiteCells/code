#include "D:/distake/Coding/head_file.h"

/*
 * @Author: WhiteCells
 * @Date: 2023-06-09 08:21:47
 * @Last Modified by: WhiteCells
 * @Last Modified time: 2023-06-09 08:21:47
 * @Description: 96. 不同的二叉搜索树
 * https://leetcode.cn/problems/unique-binary-search-trees/
*/

class Solution {
public:
    int numTrees(int n) {
        // int dp[n + 1] = { 0 };
        // int* dp = (int*)malloc(sizeof(int) * (n + 1));
        vector<int> dp(n + 2, 0);
        dp[0] = 1, dp[1] = 1, dp[2] = 2;
        for (int i = 3; i <= n; ++i) {
            for (int j = 0; j < i; ++j) {
                dp[i] += dp[j] * dp[i - j - 1]; // 左边个数 * 乘右边个数
            }
        }
        return dp[n];
    }
};

int main() {
    Solution s;
    cout << s.numTrees(4); // 14
    return 0;
}