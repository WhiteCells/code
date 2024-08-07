#include "D:/distake/Coding/head_file.h"

/*
 * @Author: WhiteCells
 * @Date: 2023-06-08 15:20:10
 * @Last Modified by: WhiteCells
 * @Last Modified time: 2023-06-08 15:20:10
 * @Description: 343. 整数拆分
 * https://leetcode.cn/problems/integer-break/
*/

class Solution {
public:
    int integerBreak(int n) {
        int dp[n + 1] = { 0 };
        dp[2] = 1;
        for (int i = 3; i <= n; ++i) { // 从第三个数开始
            for (int j = 1; j < i - 1; ++j) { // 1 到 i - 2
                dp[i] = max(dp[i], max(j * (i - j), j * dp[i - j]));
            }
        }
        return dp[n];
    }
};

// 贪心
class Solution2 {
public:
    int integerBreak(int n) {
        if (n == 2) {
            return 2;
        }
        if (n == 3) {
            return 2;
        }
        if (n == 4) {
            return 4;
        }
        int res = 1;
        while (n > 4) {
            res *= 3;
            n -= 3;
        }
        return res * n;
    }
};


int main() {
    Solution s;
    Solution2 s2;
    // cout << s.integerBreak(10);
    cout << s2.integerBreak(10);
    return 0;
}