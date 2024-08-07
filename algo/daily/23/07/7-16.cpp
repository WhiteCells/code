#include <iostream>
#include <vector>
#include <functional>

using namespace std;

class Solution {
private:
    int find(int* tree, int i) {
        if (tree[i] != i) {
            tree[i] = find(tree, tree[i]);
        }
        return i;
    }
    void merge(int* tree, vector<int>& edge) {
        int a = edge[0];
        int b = edge[1];
        if (a > b) {
            tree[a] = b;
        }
        else {
            tree[b] = a;
        }
    }
public:
    vector<int> sumOfDistancesInTree(int n, vector<vector<int>>& edges) {
        vector<int> ans;
        int tree[n];
        for (int i = 0; i < n; ++i) {
            tree[i] = i;
        }
        for (int i = 0; i < n; ++i) {
            find(tree, i);
            merge(tree, edges[i]);
        }

        return ans;
    }
};


class Solution2 {
public:
    vector<int> sumOfDistancesInTree(int n, vector<vector<int>>& edges) {
        vector<vector<int>> g(n);
        for (auto& e : edges) {
            int x = e[0], y = e[1];
            g[x].push_back(y);
            g[y].push_back(x);
        }
        vector<int> ans(n);
        vector<int> size(n, 1);
        function<void(int, int, int)> dfs = [&](int x, int fa, int depth) {
            ans[0] += depth;
            for (auto& y : g[x]) {
                if (y != fa) {
                    dfs(y, x, depth + 1);
                    size[x] += size[y];
                }
            }
        };
        dfs(0, -1, 0);
        function<void(int, int)> reroot = [&](int x, int fa) {
            for (auto& y : g[x]) {
                if (y != fa) {
                    ans[y] = ans[x] + n - 2 * size[y];
                    reroot(y, x);
                }
            }
        };
        reroot(0, -1);
        return ans;
    }
};

class Solution3 {
public:
    vector<int> sumOfDistancesInTree(int n, vector<vector<int>>& edges) {
        vector<vector<int>> g(n); // g[x] 表示 x 的所有邻居
        for (auto& e : edges) {
            int x = e[0], y = e[1];
            g[x].push_back(y);
            g[y].push_back(x);
        }

        vector<int> ans(n);
        vector<int> size(n, 1); // 注意这里初始化成 1 了，下面只需要累加儿子的子树大小
        function<void(int, int, int)> dfs = [&](int x, int fa, int depth) {
            ans[0] += depth; // depth 为 0 到 x 的距离
            for (int y : g[x]) { // 遍历 x 的邻居 y
                if (y != fa) { // 避免访问父节点
                    dfs(y, x, depth + 1); // x 是 y 的父节点
                    size[x] += size[y]; // 累加 x 的儿子 y 的子树大小
                }
            }
        };
        dfs(0, -1, 0); // 0 没有父节点

        function<void(int, int)> reroot = [&](int x, int fa) {
            for (int y : g[x]) { // 遍历 x 的邻居 y
                if (y != fa) { // 避免访问父节点
                    ans[y] = ans[x] + n - 2 * size[y];
                    reroot(y, x); // x 是 y 的父节点
                }
            }
        };
        reroot(0, -1); // 0 没有父节点
        return ans;
    }
};



int main() {
    vector<vector<int>> edges{ { 0, 1 }, { 0, 2 }, { 2, 3 }, { 2, 4 }, { 2, 5 } };
    Solution3 s;
    vector<int> ans = s.sumOfDistancesInTree(edges.size() + 1, edges);
    for (auto& ele : ans) {
        cout << ele << ' ';
    }
    return 0;
}