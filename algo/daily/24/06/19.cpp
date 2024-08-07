#include "../../head_file.h"

/*
problme: 

url: https://leetcode.cn/problems/maximum-strictly-increasing-cells-in-a-matrix/description/
 */

class Solution {
public:
    int maxIncreasingCells(vector<vector<int>>& mat) {
        int m = mat.size(), n = mat[0].size();
        map<int, vector<pair<int, int>>> g;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                g[mat[i][j]].emplace_back(i, j); // 相同元素放在同一组，统计位置
            }
        }

        vector<int> row_max(m), col_max(n);
        for (auto& [_, pos] : g) {
            // 先把所有 f 值都算出来，再更新 row_max 和 col_max
            vector<int> fs;
            for (auto& [i, j] : pos) {
                fs.push_back(max(row_max[i], col_max[j]) + 1);
            }
            for (int k = 0; k < pos.size(); k++) {
                auto& [i, j] = pos[k];
                row_max[i] = max(row_max[i], fs[k]); // 更新第 i 行的最大 f 值
                col_max[j] = max(col_max[j], fs[k]); // 更新第 j 列的最大 f 值
            }
        }
        return ranges::max(row_max);
    }
};

int main() {
    
    return 0;
}