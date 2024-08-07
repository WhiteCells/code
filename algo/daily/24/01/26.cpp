#include "../../head_file.h"

/*
problme:

url:
 */

class Solution {
public:
    vector<int> minOperationsQueries(int n, vector<vector<int>> &edges, vector<vector<int>> &queries) {
        vector<unordered_map<int, int>> path(n);
        for (const auto &edge : edges) {
            path[edge[0]][edge[1]] = edge[2];
            path[edge[1]][edge[0]] = edge[2];
        }
        vector<vector<pair<int, int>>> query_arr(n);
        for (int i = 0; i < queries.size(); ++i) {
            query_arr[queries[i][0]].push_back({queries[i][1], i});
            query_arr[queries[i][1]].push_back({queries[i][0], i});
        }

        vector<vector<int>> count(n, vector<int>(27));
        vector<int> visited(n), uf(n), lca(queries.size());
        function<void(int, int)> tarjan = [&](int node, int parent) {
            if (-1 != parent) {
                count[node] = count[parent];
                ++count[node][path[node][parent]];
            }
            uf[node] = node;
            for (const auto &[child, _] : path[node]) {
                if (child == parent) {
                    continue;
                }
                tarjan(child, node);
                uf[child] = node;
            }
            for (const auto &[node1, index] : query_arr[node]) {
                if (node != node1 && !visited[node1]) {
                    continue;
                }
                lca[index] = find(uf, node1);
            }
            visited[node] = 1;
        };
        tarjan(0, -1);
        vector<int> res(queries.size());
        for (int i = 0; i < queries.size(); ++i) {
            int total_cnt = 0, max_cnt = 0;
            for (int j = 1; j <= 26; ++j) {
                int cnt = count[queries[i][0]][j]
                    + count[queries[i][1]][j] - 2 * count[lca[i]][j];
                max_cnt = max(max_cnt, cnt);
                total_cnt += cnt;
            }
            res[i] = total_cnt - max_cnt;
        }
        return res;
    }
private:
    int find(vector<int> &uf, int n) {
        if (n == uf[n]) {
            return n;
        }
        uf[n] = find(uf, uf[n]);
        return uf[n];
    }
};

int main() {
    // [[0,1,1],[1,2,1],[2,3,1],[3,4,2],[4,5,2],[5,6,2]]
    vector<vector<int>> edges {{0, 1, 1}, {1, 2, 1}};
    vector<vector<int>> queries {{}};
    // Solution().minOperationsQueries(int n, );
    return 0;
}