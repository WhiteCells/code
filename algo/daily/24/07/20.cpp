#include "../../head_file.h"

/*
problme:

url:
 */

class Solution {
public:
    int minimumMoves(vector<vector<int>>& grid) {
        vector<pair<int, int>> from, to;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (grid[i][j]) {
                    for (int k = 1; k < grid[i][j]; k++) {
                        from.emplace_back(i, j);
                    }
                } else {
                    to.push_back({i, j});
                }
            }
        }
        // int res = INT_MAX;
        // // (x1, y1) (x2, y2)
        // // d(x, y) = |x1 - x2| + |y1 - y2|
        // function<int(int)> dfs = [&dfs](int x) -> int {
        //     if (x == 0) {
        //         return 1;
        //     }
        //     return x * dfs(x - 1);
        // };
        // int cnt = dfs((int)from.size());
        // for (int i = 0; i < cnt; ++i) {
        //     int cur = 0;
        //     for (int j = 0; j < from.size(); ++i) {
        //         cur += abs(from[j].first - to[j].first) + abs(from[j].second
        //         - to[j].second);
        //     }
        //     res = min(res, cur);
        // }
        // return res;
        int ans = INT_MAX;
        function<int(int)> dfs = [&dfs](int x) -> int {
            if (x == 1) {
                return 1;
            }
            return x * dfs(x - 1);
        };
        int cnt = dfs(from.size());
        // for (int j = 0; j < cnt; ++j) {
        do {
            int total = 0;
            for (int i = 0; i < from.size(); i++) {
                total += abs(from[i].first - to[i].first) +
                         abs(from[i].second - to[i].second);
            }
            ans = min(ans, total);
        } while (next_permutation(from.begin(), from.end()));
        // }
        return ans;
    }
};

int main() {
    // [[1,1,0],[1,1,1],[1,2,1]]
    vector<vector<int>> grid {
        {1, 1, 0},
        {1, 1, 1},
        {1, 2, 1},
    };
    cout << Solution().minimumMoves(grid) << endl;
    return 0;
}