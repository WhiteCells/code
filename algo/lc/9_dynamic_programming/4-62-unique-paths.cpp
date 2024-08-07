#include "D:/distake/Coding/head_file.h"

/*
 * @Author: WhiteCells
 * @Date: 2023-06-03 14:33:47
 * @Last Modified by: WhiteCells
 * @Last Modified time: 2023-06-03 14:33:47
 * @Description: 62. 不同路径
 * https://leetcode.cn/problems/unique-paths/
*/

// 深度优先搜索
class Solution {
private:
    int dfs(int i, int j, int m, int n) {
        if (i > m || j > n) {
            return 0;
        }
        if (i == m && j == n) {
            return 1;
        }
        return dfs(i + 1, j, m, n) + dfs(i, j + 1, m, n);
    }
public:
    int uniquePaths(int m, int n) {
        return dfs(1, 1, m, n);
    }
};


// 二维数组
class Solution2 {
public:
    int uniquePaths(int m, int n) {
        vector<vector<int>> dp(m, vector<int>(n, 0));
        for (int i = 0; i < n; ++i) {
            dp[0][i] = 1;
        }
        for (int i = 0; i < m; ++i) {
            dp[i][0] = 1;
        }
        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
            }
        }
        return dp[m - 1][n - 1];
    }
};


// 一维数组
class Solution3 {
public:
    int uniquePaths(int m, int n) {
        vector<int> dp(n, 1);
        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                dp[j] += dp[j - 1];
            }
        }
        return dp[n - 1];
    }
};


// 无论如何总步数都需要 m + n - 2 步
// 其中有 m - 1 步可以选择向下的
// C(m + n - 2, m - 1)，总步数里选择向下走的步数
class Solution4 {
private:
    int combination(int m, int n) { // C(m, n)
        int molecule = 1; // 分子
        int denominator = 1; // 分母
        for (int i = m; i > m - n; --i) { // 分子 n(n - 1)...(m - n + 1)
            molecule *= i;
        }
        for (int i = n; i > 0; --i) { // 分母 n!
            denominator *= i;
        }
        return molecule / denominator; // 会溢出
    }
public:
    int uniquePaths(int m, int n) {
        return combination(m + n - 2, m - 1);
    }
};


// 边求分子边除以分母，防止溢出
class Solution5 {
public:
    int uniquePaths(int m, int n) {
        int res = 1;
        // 求分子
        return 1;
    }
};


int main() {
    Solution s1;
    Solution2 s2;
    Solution3 s3;
    Solution4 s4;
    cout << s1.uniquePaths(3, 7) << '\n';
    cout << s2.uniquePaths(3, 7) << '\n';
    cout << s3.uniquePaths(3, 7) << '\n';
    cout << s4.uniquePaths(3, 7) << '\n';
    return 0;
}