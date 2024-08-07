#include <iostream>
#include <vector>
#include <functional>
#include <array>

using namespace std;

class Solution {
public:
    int uniquePathsIII(vector<vector<int>>& grid) {
        // 找起点和统计路径长
        int len = 0, si = 0, sj = 0;
        int row = grid.size(), col = grid[0].size();
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; ++j) {
                if (0 == grid[i][j]) {
                    ++len;
                }
                else if (1 == grid[i][j]) {
                    ++len;
                    si = i;
                    sj = j;
                }
            }
        }
        // dfs 从 si sj 开始搜索 长度为 len 的路径
        function<int(int, int, int)> dfs = [&](int si, int sj, int len)->int {
            // 搜索到终点
            if (2 == grid[si][sj]) {
                // 路径长度为 len
                if (0 == len) {
                    return 1;
                }
                return 0;
            }
            // 记录，移动后还原
            int tmp = grid[si][sj];
            int res = 0;
            // 走过的标记 -1
            grid[si][sj] = -1;
            // 4 个方向
            vector<array<int, 2>> dir({ { -1, 0 }, { 1, 0 }, { 0, -1 }, { 0, 1 } });
            // for (auto& [di, dj] : dir) {
            //     int next_i = si + di;
            //     int next_j = sj + dj;
            //     if (next_j >= 0 && next_i >= 0 && next_j < col && next_i < row \
            //         && (0 == grid[next_i][next_j] || 2 == grid[next_i][next_j])) {
            //         res += dfs(next_i, next_j, len - 1);
            //     }
            // }
            // 遍历 4 个方向
            for (const auto& d : dir) {
                int next_i = si + d[0];
                int next_j = sj + d[1];
                if (next_i >= 0 && next_j >= 0 && next_i < row && next_j <= col \
                    && (0 == grid[next_i][next_j] || 2 == grid[next_i][next_j])) { // 下标合法才能访问
                    res += dfs(next_i, next_j, len - 1);
                }
            }
            // 还原
            grid[si][sj] = tmp;
            return res;
        };
        return dfs(si, sj, len);
    }
};

int main() {
    vector<vector<int>> grid{
        { 1, 0, 0, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 2, -1 }
    };
    Solution s;
    cout << s.uniquePathsIII(grid) << '\n';
    return 0;
}