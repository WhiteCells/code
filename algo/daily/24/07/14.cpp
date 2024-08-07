#include "../../head_file.h"

/*
problme:

url: https://leetcode.cn/problems/max-increase-to-keep-city-skyline/
 */

class Solution {
public:
    int maxIncreaseKeepingSkyline(vector<vector<int>> &grid) {
        vector<int> row, col;
        for (const auto &r : grid) {
            row.push_back(*max(r.begin(), r.end()));
        }
        for (size_t j = 0; j < grid[0].size(); ++j) {
            int mx = grid[0][j];
            for (size_t i = 0; i < grid.size(); ++i) {
                mx = max(mx, grid[i][j]);
            }
            col.push_back(mx);
        }
        int res = 0;
        for (size_t i = 0; i < grid.size(); ++i) {
            for (size_t j = 0; j < grid[0].size(); ++j) {
                if (grid[i][j] == row[i] || grid[i][j] == col[j]) {
                    continue;
                }
                res += min(row[i], col[j]);
            }
        }
        return res;
    }
};

int main() {

    return 0;
}