#include "../../head_file.h"

/*
problme:

url:
*/

/*
dp[i][j] : i 行 j 列上是否有主机
 */
class Solution {
public:
    int countServers(vector<vector<int>>& grid) {
        int row[250] = { 0 }, col[250] = { 0 };
        int m = grid.size(), n = grid[0].size();
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j]) {
                    ++row[i];
                    ++col[j];
                }
            }
        }
        int res = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                res += grid[i][j] & (row[i] > 1 | col[j] > 1);
            }
        }
        return res;
    }
};

int main() {
    vector<vector<int>> grid { { 1, 1, 0, 0 }, { 0, 0, 1, 0 }, { 0, 0, 1, 0 }, { 0, 0, 0, 1 } };
    // vector<vector<int>> grid { { 1, 0 }, { 1, 1 } };
    Solution s;
    cout << s.countServers(grid) << '\n';
    return 0;
}