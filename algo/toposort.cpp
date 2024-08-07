#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// 代码的核心是维持一个入度为 0 的顶点的集合
bool topoSort(vector<vector<int>> &g, vector<int> &in) {
    vector<int> topoSortRes; // 存放拓扑序列
    queue<int> zeroIn; // 入度为零的点的集合
    // 队列中放入度为 0 的点
    for (int i = 0; i < g.size(); ++i) {
        if (in[i] == 0) {
            zeroIn.push(i);
        }
    }
    while (!zeroIn.empty()) {
        // 取出度为 0 的点
        int u = zeroIn.front();
        zeroIn.pop();
        // 放入拓扑序列
        topoSortRes.push_back(u);
        // 遍历度为 0 的点的所有后继点
        for (const auto &v : g[u]) {
            if (--in[v] == 0) {
                zeroIn.push(v);
            }
        }
    }
    if (topoSortRes.size() != g.size()) {
        return false;
    }
    for (const auto &ele : topoSortRes) {
        cout << ele << ' ';
    }
    return true;
}

int main() {
    int m = 0, n = 0; // m 个节点（0~m-1），n 个边
    cin >> m >> n;
    vector<vector<int>> g(m);
    vector<int> in(m);
    for (int i = 0; i < n; ++i) {
        int f, t;
        cin >> f >> t;
        g[f].push_back(t);
        ++in[t];
    }
    if (topoSort(g, in)) {
        cout << "DAG" << endl;
    }
    return 0;
}