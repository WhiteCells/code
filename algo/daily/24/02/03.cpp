#include "../../head_file.h"

/*
problme: 
输入：stones = [5,3,1,4,2]
               0,5,8,9,13,15
输出：6
url: https://leetcode.cn/problems/stone-game-vii/description/
 */

// dfs
class Solution {
public:
    int stoneGameVII(vector<int>& stones) {
        // 记 f(i, j) 表示 [i, j] 的最大差值
        // f(i, j) = max(sum(i + 1, j) - f(i + 1, j), sum(i, j - 1), f(i, j - 1))
        int n = stones.size();
        vector<int> prev(n + 1);
        for (int i = 0; i < n; ++i) {
            prev[i + 1] = prev[i] + stones[i];
        }
        vector<vector<int>> memo(n, vector<int>(n, 0));
        function<int(int, int)> dfs = [&](int i, int j) -> int {
            if (i >= j) {
                return 0;
            }
            if (memo[i][j]) {
                return memo[i][j];
            }
            memo[i][j] = max(prev[j + 1] - prev[i + 1] - dfs(i + 1, j),
                             prev[j] - prev[i] - dfs(i, j - 1));
            return memo[i][j];
        };
        return dfs(0, n - 1);
    }
};

// dp
class Solution2 {
public:
    int stoneGameVII(vector<int> &stones) {
        int n = stones.size();
        vector<int> prev(n + 1);
        for (int i = 0; i < n; ++i) {
            prev[i + 1] = prev[i] + stones[i];
        }
        // 记 dp[i][j] 表示 [i, j] 最大差值
        vector<vector<int>> dp(n, vector<int>(n));
        for (int i = n - 2; i >= 0; --i) {
            for (int j = i + 1; j < n; ++j) {
                dp[i][j] = max(prev[j + 1] - prev[i + 1] - dp[i + 1][j],
                               prev[j] - prev[i] - dp[i][j - 1]);
            }
        }
        return dp[0][n - 1];
    }
};

int main() {
    vector<int> stones {5, 3, 1, 4, 2};
    cout << Solution().stoneGameVII(stones) << endl;
    cout << Solution2().stoneGameVII(stones) << endl;
    return 0;
}