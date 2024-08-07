#include "../../head_file.h"

class Solution {
public:
    int minReorder(int n, vector<vector<int>> &connections) {
        vector<vector<pair<int, int>>> g(n); // from <to : 是否连通>
        for (const auto &edge : connections) {
            int from = edge[0], to = edge[1];
            g[from].push_back(make_pair(to, 1));
            g[to].push_back(make_pair(from, 0));
        }
        function<int(int, int)> dfs = [&](int from, int father) -> int {
            // 统计从 0 开始向别城市不连通的边
            int res = 0;
            // 遍历 x 点连通的边
            for (const auto &edge : g[from]) {
                auto &[to, flag] = edge;
                if (to == father) {
                    continue;
                }
                res += flag + dfs(to, from);
            }
            return res;
        };
        return dfs(0, -1);
    }
};

int main() {
    // [[0,1],[1,3],[2,3],[4,0],[4,5]]
    // int n = 6
    vector<vector<int>> connections {
        {0, 1},
        {1, 3},
        {2, 3},
        {4, 0},
        {4, 5},
    };
    int n = 6;
    cout << Solution().minReorder(n, connections) << endl;
    return 0;
}