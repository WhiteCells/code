#include "../../head_file.h"

/*
problme:

url:
 */

class Solution {
public:
    vector<int> countPairsOfConnectableServers(vector<vector<int>> &edges, int signalSpeed) {
        int n = edges.size() + 1; // 边比节点数少 1
        // {root, [<child1, cost1>, <child2, cost2>, ..., <childn, costn>]}
        vector<vector<pair<int, int>>> graph(n);

        for (const auto &edge : edges) {
            graph[edge[0]].push_back({edge[1], edge[2]});
            graph[edge[1]].push_back({edge[1], edge[2]});
        }

        /// @brief 
        /// @param root 根节点，传入该参数是为了防止子树根节点走向该节点
        /// @param child 子节点
        /// @param remainder root 到 child 的根节点的距离
        /// @return 返回以 root 根节点，child 为其中一个子树，子树有多少个满足到达路径可以被 signalSpeed 整除的节点
        function<int(int, int, int)> dfs = [&](int root, int child, int remainder) -> int {
            int res = 0;
            if (remainder == 0) {
                ++res;
            }

            // 遍历子节点的所有子树
            for (const auto &[j, cost] : graph[child]) {
                // 排除根节点路径
                if (j != root) {
                    res += dfs(child, j, (remainder + cost) % signalSpeed);
                }
            }
            return res;
        };

        vector<int> res(n);

        // 遍历根节点
        for (int i = 0; i < n; ++i) {
            int pre = 0; // 统计根节点子树的可连接对数

            // 遍历根节点的所有子树
            for (auto &[j, cost] : graph[i]) {
                // 当前子树满足的条件的节点个数
                int cnt = dfs(i, j, cost % signalSpeed);
                res[i] += pre * cnt;
                pre += cnt;
            }
        }
        return res;
    }
};

int main() {
    return 0;
}