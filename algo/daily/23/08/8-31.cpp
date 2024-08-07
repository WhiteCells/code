#include "../../head_file.h"

/*
problme: 1761. 一个图中连通三元组的最小度数
给你一个无向图，整数 n 表示图中节点的数目，edges 数组表示图中的边，其中 edges[i] = [ui, vi] ，表示 ui 和 vi 之间有一条无向边。

一个 连通三元组 指的是 三个 节点组成的集合且这三个点之间 两两 有边。

连通三元组的度数 是所有满足此条件的边的数目：一个顶点在这个三元组内，而另一个顶点不在这个三元组内。

请你返回所有连通三元组中度数的 最小值 ，如果图中没有连通三元组，那么返回 -1 。
输入：n = 6, edges = [[1,2],[1,3],[3,2],[4,1],[5,2],[3,6]]
输出：3
解释：只有一个三元组 [1,2,3] 。构成度数的边在上图中已被加粗。

提示：

    2 <= n <= 400
    edges[i].length == 2
    1 <= edges.length <= n * (n-1) / 2
    1 <= ui, vi <= n
    ui != vi
    图中没有重复的边。

url: https://leetcode.cn/problems/minimum-degree-of-a-connected-trio-in-a-graph/
*/

class Solution {
public:
    int minTrioDegree(int n, vector<vector<int>>& edges) {
        // ui,vi : [1, n] G 记录连接关系，d 记录每个点的度
        int G[401][401] = { 0 }, d[401] = { 0 }, mn = INT_MAX;
        for (auto &e : edges) {
            int x = e[0], y = e[1];
            // 建立连接
            G[x][y] = G[y][x] = 1;
            // 度增加
            d[x]++;
            d[y]++;
        }
        for (int i = 1; i <= n; i++) {
            for (int j = i + 1; j <= n; j++) {
                for (int k = j + 1; k <= n; k++) {
                    // i j k 之间有连接，如果 i j k 点之间有连接则 G[i][j] G[i][k] G[j][k] 都存在
                    if (G[i][j] && G[j][k] && G[i][k]) {
                        // i j k 点的度相加 减去 6
                        // 假设一个三元组中任意一个点的度都为另外两个数，此时所有度相加 == 6
                        //      1
                        //     / \
                        //    2 - 3
                        mn = min(mn, d[i] + d[j] + d[k] - 6);
                    }
                }
            }
        }
        return mn == INT_MAX ? -1 : mn;
    }
};

int main() {
    // 输入：n = 7, edges = [[1,3],[4,1],[4,3],[2,5],[5,6],[6,7],[7,5],[2,6]]
    // int n = 7;
    // vector<vector<int>> edges {
    //     { 1, 3 },
    //     { 4, 1 },
    //     { 4, 3 },
    //     { 2, 5 },
    //     { 5, 6 },
    //     { 6, 7 },
    //     { 7, 5 },
    //     { 2, 6 }
    // };

    // 输入：n = 6, edges = [[1,2],[1,3],[3,2],[4,1],[5,2],[3,6]]
    int n = 6;
    vector<vector<int>> edges {
        { 1, 2 },
        { 1, 3 },
        { 3, 2 },
        { 4, 1 },
        { 5, 2 },
        { 3, 6 }
    };
    cout << Solution().minTrioDegree(n, edges) << '\n';
    return 0;
}