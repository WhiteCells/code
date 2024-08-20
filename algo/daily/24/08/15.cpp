#include "../../head_file.h"

/*
problme:

url:
 */
class Solution {
public:
    int maxScore(vector<vector<int>>& grid) {
        int ans = INT_MIN;
        int m = grid.size(), n = grid[0].size();
        vector<vector<int>> f(m + 1, vector<int>(n + 1, INT_MAX));
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                int mn = min(f[i + 1][j], f[i][j + 1]);
                ans = max(ans, grid[i][j] - mn);
                f[i + 1][j + 1] = min(mn, grid[i][j]);
            }
        }
        return ans;
    }
};

int main() {

    return 0;
}