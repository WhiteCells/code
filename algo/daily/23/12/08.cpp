#include "../../head_file.h"

/*
problme:

url:
 */

class Solution {
public:
    long long maxTaxiEarnings(int n, vector<vector<int>> &rides) {
        vector<vector<pair<int, int>>> g(n + 1); // <end : <start : tip>>
        for (const auto &r : rides) {
            int s = r[0], e = r[1], t = r[2];
            g[e].push_back(make_pair(s, e - s + t));
        }
        // dfs(i) = max(dfs(i - 1), max{dfs(s) + i - s + tip})
        // 从 1 开始出发，递归终点(边界)就是 1，dfs(1) = 0
        vector<long long> memo(n + 1, -1);
        function<long long(int)> dfs = [&](int i) -> long long {
            if (1 == i) {
                return 0;
            }
            if (-1 != memo[i]) {
                return memo[i];
            }
            long long income = dfs(i - 1);
            // 遍历当前出发地点向后的最大收益
            for (const auto &[s, t] : g[i]) {
                income = max(income, dfs(s) + t);
            }
            return memo[i] = income;
        };
        return dfs(n);
    }
};

int main() {
    // [[2,5,4],[1,5,1]]
    // 5
    vector<vector<int>> rides {
        {2, 5, 4},
        {1, 5, 1},
    };
    int n = 5;
    cout << Solution().maxTaxiEarnings(n, rides) << endl;
    return 0;
}