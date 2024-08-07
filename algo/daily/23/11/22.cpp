#include "../../head_file.h"

/*
problme:
grid = [[5,3],[4,0],[2,1]],
moveCost = [[9,8],[1,5],[10,12],[18,6],[2,4],[14,3]]
url: https://leetcode.cn/problems/minimum-path-cost-in-a-grid/description/
 */

class Solution {
public:
    int minPathCost(vector<vector<int>> &grid, vector<vector<int>> &moveCost) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<int>> dp(2, vector<int>(n));
        dp[0] = grid[0];
        int cur = 0;
        for (int i = 1; i < m; ++i) {
            int next = 1 - cur;
            for (int j = 0; j < n; ++j) {
                dp[next][j] = INT_MAX;
                for (int k = 0; k < n; ++k) {
                    dp[next][j] = min(dp[next][j], dp[cur][k] + moveCost[grid[i - 1][k]][j] + grid[i][j]);
                }
            }
            cur = next;
        }
        return *min_element(dp[cur].begin(), dp[cur].end());
    }
};

class Solution2 {
public:
    int minPathCost(vector<vector<int>> &grid, vector<vector<int>> &moveCost) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<int>> memo(m, vector<int>(n, -1));
        function<int(int, int)> dfs = [&](int i, int j) -> int {
            if (0 == i) {
                return grid[i][j];
            }
            if (-1 != memo[i][j]) {
                return memo[i][j];
            }
            int res = INT_MAX;
            for (int k = 0; k < n; ++k) {
                res = min(res, dfs(i - 1, k) + moveCost[grid[i - 1][k]][j] + grid[i][j]);
            }
            return memo[i][j] = res;
        };
        int res = INT_MAX;
        for (int j = 0; j < n; ++j) {
            res = min(res, dfs(m - 1, j));
        }
        return res;
    }
};

int main() {
    vector<vector<int>> grid {
        {5, 3},
        {4, 0},
        {2, 1},
    };
    vector<vector<int>> moveCost {
        {9, 8},
        {1, 5},
        {10, 12},
        {18, 6},
        {2, 4},
        {14, 3},
    };
    cout << Solution2().minPathCost(grid, moveCost) << endl;
    return 0;
}