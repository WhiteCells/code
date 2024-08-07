#include "../../head_file.h"

/*
problme: 2316. 统计无向图中无法互相到达点对数

给你一个整数 n ，表示一张 无向图 中有 n 个节点，编号为 0 到 n - 1 。同时给你一个二维整数数组 edges ，其中 edges[i] = [ai, bi] 表示节点 ai 和 bi 之间有一条 无向 边。

请你返回 无法互相到达 的不同 点对数目 。


示例 1：

输入：n = 3, edges = [[0,1],[0,2],[1,2]]
输出：0
解释：所有点都能互相到达，意味着没有点对无法互相到达，所以我们返回 0 。

示例 2：

输入：n = 7, edges = [[0,2],[0,5],[2,4],[1,6],[5,4]]
输出：14
解释：总共有 14 个点对互相无法到达：
[[0,1],[0,3],[0,6],[1,2],[1,3],[1,4],[1,5],[2,3],[2,6],[3,4],[3,5],[3,6],[4,6],[5,6]]
所以我们返回 14 。

提示：

    1 <= n <= 105
    0 <= edges.length <= 2 * 105
    edges[i].length == 2
    0 <= ai, bi < n
    ai != bi
    不会有重复边。

url: https://leetcode.cn/problems/count-unreachable-pairs-of-nodes-in-an-undirected-graph/description/
 */

// time complexity: O()
// spatial complexity: O()
class Solution {
public:
    long long countPairs(int n, vector<vector<int>> &edges) {
        UnionFind uf(n);
        for (const auto &edge : edges) {
            uf.unionSet(edge[0], edge[1]);
        }
        long long res = 0;
        for (int i = 0; i < n; ++i) {
            res += n - uf.getSize(uf.findSet(i));
        }
        return res / 2;
    }
private:
    class UnionFind {
    public:
        UnionFind(int n) : parents(n), sizes(n, 1) {
            iota(parents.begin(), parents.end(), 0);
        }
        int findSet(int x) {
            if (x == parents[x]) {
                return x;
            }
            return parents[x] = findSet(parents[x]);
        }
        void unionSet(int x, int y) {
            int rx = findSet(x), ry = findSet(y);
            if (rx != ry) {
                if (sizes[rx] > sizes[ry]) {
                    parents[ry] = rx;
                    sizes[rx] += sizes[ry];
                } else {
                    parents[rx] = ry;
                    sizes[ry] += sizes[rx];
                }
            }
        }
        int getSize(int x) {
            return sizes[x];
        }
    private:
        vector<int> parents;
        vector<int> sizes; // 每一个集合的长度
    };
};

int main() {
    
    return 0;
}