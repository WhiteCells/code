#include "../../head_file.h"

/*
problme: 1444. 切披萨的方案数
给你一个 rows x cols 大小的矩形披萨和一个整数 k ，矩形包含两种字符： 'A' （表示苹果）和 '.' （表示空白格子）。你需要切披萨 k-1 次，得到 k 块披萨并送给别人。
切披萨的每一刀，先要选择是向垂直还是水平方向切，再在矩形的边界上选一个切的位置，将披萨一分为二。如果垂直地切披萨，那么需要把左边的部分送给一个人，如果水平地切，那么需要把上面的部分送给一个人。在切完最后一刀后，需要把剩下来的一块送给最后一个人。
请你返回确保每一块披萨包含 至少 一个苹果的切披萨方案数。由于答案可能是个很大的数字，请你返回它对 10^9 + 7 取余的结果。
输入：pizza = ["A..","AAA","..."], k = 3
输出：3
解释：上图展示了三种切披萨的方案。注意每一块披萨都至少包含一个苹果。
提示：
    1 <= rows, cols <= 50
    rows == pizza.length
    cols == pizza[i].length
    1 <= k <= 10
    pizza 只包含字符 'A' 和 '.' 。
url: https://leetcode.cn/problems/number-of-ways-of-cutting-a-pizza/
@Author: Eorys
@Date: 2023-08-17 06:06:50
@Last Modified by: Eorys
@Last Modified time: 2023-08-17 06:06:50
@Description:
*/

class Solution {
public:
    int ways(vector<string>& pizza, int k) {
        int m = pizza.size(), n = pizza[0].size(), mod = 1e9 + 7;
        vector<vector<int>> cnts(m, vector<int>(n, 0));
        for (int i = m - 1; i >= 0; --i) {
            for (int j = n - 1; j >= 0; --j) {
                // 右下角
                if (m - 1 == i && n - 1 == j) {
                    cnts[i][j] = ('A' == pizza[i][j]);
                }
                // 下边
                else if (m - 1 == i) {
                    cnts[i][j] = cnts[i][j + 1] + ('A' == pizza[i][j]);
                }
                // 右边
                else if (n - 1 == j) {
                    cnts[i][j] = cnts[i + 1][j] + ('A' == pizza[i][j]);
                }
                // 其他位置
                else {
                    cnts[i][j] = cnts[i + 1][j] + cnts[i][j + 1] - cnts[i + 1][j + 1] + ('A' == pizza[i][j]);
                }
            }
        }
        vector<vector<vector<int>>> dp(m, vector<vector<int>>(n, vector<int>(k, 0)));
        for (int h = 0; h < k; ++h) {
            for (int i = m - 1; i >= 0; --i) {
                for (int j = n - 1; j >= 0; --j) {
                    if (0 == h) {
                        dp[i][j][h] = (cnts[i][j] > 0);
                    }
                    else {
                        for (int x = i; x < m - 1; ++x) {
                            if (cnts[i][j] - cnts[x + 1][j] > 0) {
                                dp[i][j][h] = (dp[i][j][h] + dp[x + 1][j][h - 1]) % mod;
                            }
                        }
                        for (int y = j; y < n - 1; ++y) {
                            if (cnts[i][j] - cnts[i][y + 1] > 0) {
                                dp[i][j][h] = (dp[i][j][h] + dp[i][y + 1][h - 1]) % mod;
                            }
                        }
                    }
                }
            }
        }
        return dp[0][0][k - 1];
    }
};

int main() {
    vector<string> pizza {
        "A..",
        "AAA",
        "..."
    };
    int k = 3;
    // vector<string> pizza {
    //     "...",
    //     "...",
    //     "..."
    // };
    // int k = 1;
    Solution s;
    cout << s.ways(pizza, k) << '\n';
    return 0;
}