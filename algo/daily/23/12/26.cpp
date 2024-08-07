#include "../../head_file.h"

/*
problme:

url: https://leetcode.cn/problems/maximum-students-taking-exam/description/
 */

// TODO
class Solution {
public:
    int maxStudents(vector<vector<char>> &seats) {
        int m = seats.size(), n = seats[0].size();
        vector<int> ss(m);
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (seats[i][j] == '.') {
                    ss[i] |= 1 << j;
                }
            }
        }
        vector<vector<int>> memo(1 << n, vector<int>(m, -1));
        function<int(int, int)> dfs = [&](int seat, int i) -> int {
            if (memo[seat][i] != -1) {
                return memo[seat][i];
            }
            int res = 0;
            for (int mask = 0; mask < 1 << n; ++mask) {
                if ((seat | mask) != seat || (mask & (mask << 1)) != 0) {
                    continue;
                }
                int cnt = __builtin_popcount(mask);
                if (i == m - 1) {
                    res = max(res, cnt);
                } else {
                    int next = ss[i + 1];
                    next &= ~(mask >> 1);
                    next &= ~(mask << 1);
                    res = max(res, cnt + dfs(next, i + 1));
                }
            }
            return memo[seat][i] = res;
        };
        return dfs(ss[0], 0);
    }
};

int main() {
    vector<vector<char>> seats {
        {'#', '.', '#', '#', '.', '#'},
        {'.', '#', '#', '#', '#', '.'},
        {'#', '.', '#', '#', '.', '#'},
    };
    cout << Solution().maxStudents(seats) << endl;
    return 0;
}