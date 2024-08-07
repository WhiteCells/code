#include "D:/distake/Coding/head_file.h"

/*
 * @Author: WhiteCells
 * @Date: 2023-06-01 23:21:54
 * @Last Modified by: WhiteCells
 * @Last Modified time: 2023-06-01 23:21:54
 * @Description: 70. 爬楼梯
 * https://leetcode.cn/problems/climbing-stairs/
*/

class Solution {
public:
    int climbStairs(int n) {
        if (n <= 0) {
            return 0;
        }
        if (n == 1) {
            return 1;
        }
        if (n == 2) {
            return 2;
        }
        return climbStairs(n - 1) + climbStairs(n - 2);
    }
};

class Solution2 {
public:
    int climbStairs(int n) {
        if (n == 1 || n == 2 || n == 3) {
            return n;
        }
        int dp[3] = { 1, 2, 3 };
        for (int i = 3; i < n; ++i) {
            dp[0] = dp[1];
            dp[1] = dp[2];
            dp[2] = dp[0] + dp[1];
        }
        return dp[2];
    }
};

int main() {
    Solution s;
    int n = 44;
    cout << s.climbStairs(10) << endl;
    cout << s.climbStairs(10) << endl;

    Solution2 s2;
    cout << s2.climbStairs(10) << endl;
    cout << s2.climbStairs(10) << endl;
    return 0;
}