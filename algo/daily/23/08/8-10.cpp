#include <iostream>
#include <vector>
#include <functional>

using namespace std;
// https://leetcode.cn/problems/minimum-falling-path-sum-ii/

// 输入：grid = [
// [1,2,3],
// [4,5,6],
// [7,8,9]]
// 输出：13
// 解释：
// 所有非零偏移下降路径包括：
// [1,5,9], [1,5,7], [1,6,7], [1,6,8],
// [2,4,8], [2,4,9], [2,6,7], [2,6,8],
// [3,4,8], [3,4,9], [3,5,7], [3,5,9]
// 下降路径中数字和最小的是 [1,5,7] ，所以答案是 13 。

class Solution {
public:
    int minFallingPathSum(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        for (int i = 1; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                int min_val = INT_MAX;
                for (int k = 0; k < n; ++k) {
                    if (k != j) {
                        min_val = min(min_val, grid[i - 1][k]);
                    }
                }
                grid[i][j] += min_val;
            }
        }
        int res = INT_MAX;
        for (int j = 0; j < n; ++j) {
            res = min(res, grid[m - 1][j]);
        }
        return res;
    }
};

int main() {
    auto grid = vector<vector<int>> { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } };
    Solution s;
    cout << s.minFallingPathSum(grid);
    return 0;
}