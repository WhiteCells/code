#include "../../head_file.h"

/*
problme: 1155. 掷骰子等于目标和的方法数

这里有 n 个一样的骰子，每个骰子上都有 k 个面，分别标号为 1 到 k 。

给定三个整数 n ,  k 和 target ，返回可能的方式(从总共 kn 种方式中)滚动骰子的数量，使正面朝上的数字之和等于 target 。

答案可能很大，你需要对 109 + 7 取模 。
 

示例 1：

输入：n = 1, k = 6, target = 3
输出：1
解释：你扔一个有 6 个面的骰子。
得到 3 的和只有一种方法。

示例 2：

输入：n = 2, k = 6, target = 7
输出：6
解释：你扔两个骰子，每个骰子有 6 个面。
得到 7 的和有 6 种方法：1+6 2+5 3+4 4+3 5+2 6+1。

示例 3：

输入：n = 30, k = 30, target = 500
输出：222616187
解释：返回的结果必须是对 109 + 7 取模。


提示：

    1 <= n, k <= 30
    1 <= target <= 1000

url: https://leetcode.cn/problems/number-of-dice-rolls-with-target-sum/description/
 */

// time complexity: O()
// spatial complexity: O()
class Solution1 {
public:
    int numRollsToTarget(int n, int k, int target) {
        int memory[41][1001], mod = 1e9 + 7;
        memset(memory, -1, sizeof(memory));
        function<int(int, int)> dfs = [&](int c, int t) ->int {
            if (~memory[c][t]) {
                return memory[c][t];
            }
            if (c == n) {
                return memory[c][t] = (t == 0);
            }
            if (1 * (n - c) > t || k * (n - c) < t || c > n) { // 最小的情况和最大的情况都无法满足和为 target
                return memory[c][t] = 0;
            }
            int sum = 0;
            for (int i = 1; i <= k && i <= t; ++i) {
                sum = (sum + dfs(c + 1, t - i)) % mod;
            }
            return memory[c][t] = sum;
        };
        return dfs(0, target);
    }
};

class Solution2 {
public:
    int numRollsToTarget(int n, int k, int target) {
        int mod = 1e9 + 7;
        vector<vector<int>> dp(n + 1, vector<int>(target + 1));
        dp[0][0] = 1;
        for (int i = 1; i <= n; ++i) { // 使用 i 个骰子
            for (int j = 0; j <= target; ++j) { // 总和 j
                for (int x = 1; x <= k; ++x) { // 骰子正面数
                    if (j >= x) {
                        dp[i][j] = (dp[i][j] + dp[i - 1][j - x]) % mod;
                    }
                }
            }
        }
        return dp[n][target];
    }
};

int main() {
    cout << Solution1().numRollsToTarget(30, 30, 500) << endl;
    cout << Solution2().numRollsToTarget(30, 30, 500) << endl;
    return 0;
}