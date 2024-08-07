#include <iostream>
#include <vector>
#include <climits>

using namespace std;

void floyd(vector<vector<int>> &g, vector<vector<int>> &path) {
    int n = g.size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                // g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
                if (i != j && k != i && k != j && g[i][j] > g[i][k] + g[k][j]) {
                    g[i][j] = g[i][k] + g[k][j];
                    path[i][j] = k;
                }
            }
        }
    }
}

int main() {
    int n = 4; // 4 个点（0~3）
    vector<vector<int>> edges {
        {0, 1, 2},
        {0, 3, 7},
        {1, 2, 3},
        {1, 3, 8},
        {2, 0, 3},
        {2, 1, 3},
        {2, 3, 1},
        {3, 2, 1},
    };
    vector<vector<int>> g(n, vector<int>(n, INT_MAX / 2)); // 邻接矩阵
    vector<vector<int>> path(n, vector<int>(n)); // 中间点
    for (const auto &e : edges) {
        int f = e[0], t = e[1], w = e[2];
        g[f][t] = w;
    }
    floyd(g, path);
    cout << g[0][3] << endl;
    return 0;
}