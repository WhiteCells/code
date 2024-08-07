#include "../../head_file.h"

/*
problme: 1782. 统计点对的数目
给你一个无向图，无向图由整数 n  ，表示图中节点的数目，和 edges 组成，其中 edges[i] = [ui, vi] 表示 ui 和 vi 之间有一条无向边。同时给你一个代表查询的整数数组 queries 。
第 j 个查询的答案是满足如下条件的点对 (a, b) 的数目：
    a < b
    cnt 是与 a 或者 b 相连的边的数目，且 cnt 严格大于 queries[j] 。
请你返回一个数组 answers ，其中 answers.length == queries.length 且 answers[j] 是第 j 个查询的答案。
请注意，图中可能会有 重复边 。
输入：n = 4, edges = [[1,2],[2,4],[1,3],[2,3],[2,1]], queries = [2,3]
输出：[6,5]
解释：每个点对中，与至少一个点相连的边的数目如上图所示。
提示：
    2 <= n <= 2 * 10^4
    1 <= edges.length <= 10^5
    1 <= ui, vi <= n
    ui != vi
    1 <= queries.length <= 20
    0 <= queries[j] < edges.length
url: https://leetcode.cn/problems/count-pairs-of-nodes/
*/

/*
edges 表示 a 和 b 的边
与点对 a，b 相连的边等于与 a 相连的边 + 与 b 相连的边 - 同时与 a，b 相连的边
求 a 和 b 相连的边数，可以使用二维数组来维护，但是 n 的范围较大，所以使用 哈希表
对于任意边 (p1, p2), pmax = max(p1, p2), pmin = min(p1, p2)
可以将边 (p1, p2) 映射到 pmax * (n + 1) + pmin

 */
class Solution {
public:
    vector<int> countPairs(int n, vector<vector<int>>& edges, vector<int>& queries) {
        vector<int> degree(n);
        unordered_map<int, int> cnt;
        for (const auto& edge : edges) {
            int x = edge[0] - 1, y = edge[1] - 1;
            if (x > y) {
                swap(x, y);
            }
            ++degree[x];
            ++degree[y];
            ++cnt[x * n + y];
        }
        vector<int> arr = degree;
        vector<int> ans;
        sort(arr.begin(), arr.end());
        for (int bound : queries) {
            int total = 0;
            for (int i = 0; i < n; ++i) {
                int j = upper_bound(arr.begin() + i + 1, arr.end(), bound - arr[i]) - arr.begin();
                total += n - j;
            }
            for (const auto& [val, freq] : cnt) {
                int x = val / n;
                int y = val % n;
                if (degree[x] + degree[y] > bound && degree[x] + degree[y] - freq <= bound) {
                    --total;
                }
            }
            ans.emplace_back(total);
        }
        return ans;
    }
};

int main() {
    int n = 4;
    vector<vector<int>> edges { { 1, 2 }, { 2, 4 }, { 1, 3 }, { 2, 3 }, { 2, 1 } };
    vector<int> queries { 2, 3 };

    Solution s;
    vector<int> res = s.countPairs(n, edges, queries);
    for (const auto& ele : res) {
        cout << ele << ' ';
    }
    cout << '\n';
    return 0;
}