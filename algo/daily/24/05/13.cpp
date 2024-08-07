#include "../../head_file.h"

/*
problme:

url: https://leetcode.cn/problems/rotting-oranges/description/
 */

class Solution {
public:
    int orangesRotting(vector<vector<int>> &grid) {
        int m = grid.size(), n = grid[0].size(), fresh_count = 0;
        queue<pair<int, int>> rot_point;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 2) {
                    rot_point.push({i, j});
                } else if (grid[i][j] == 1) {
                    ++fresh_count;
                }
            }
        }

        int res = 0;
        vector<pair<int, int>> dirs = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        while (!rot_point.empty()) {
            bool flag = false;
            int k = rot_point.size();
            for (int i = 0; i < k; ++i) {
                auto point = rot_point.front();
                rot_point.pop();
                for (const auto &dir : dirs) {
                    int x = point.first + dir.first;
                    int y = point.second + dir.second;
                    if (x >= 0 && x < m && y >= 0 && y < n && grid[x][y] == 1) {
                        flag = true;
                        grid[x][y] = 2;
                        rot_point.push({x, y});
                        --fresh_count;
                    }
                }
            }
            if (flag) {
                ++res;
            }
        }
        return fresh_count > 0 ? -1 : res;
    }
};


int main() {

    return 0;
}