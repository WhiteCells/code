#include "../../head_file.h"

/*
problme:

url:
 */

// time complexity: O()
// spatial complexity: O()
class Solution {
public:
    int maximumInvitations(vector<int> &favorite) {
        // 计算入度
        int n = favorite.size();
        vector<int> indeg(n);
        for (int i = 0; i < n; ++i) {
            ++indeg[favorite[i]];
        }
        // 初始化变量
        vector<int> used(n), f(n, 1);
        queue<int> q;
        // 将入度为0的点加入队列
        for (int i = 0; i < n; ++i) {
            if (!indeg[i]) {
                q.push(i);
            }
        }
        // 拓扑排序
        while (!q.empty()) {
            int u = q.front();
            used[u] = 1;
            q.pop();
            int v = favorite[u];
            f[v] = max(f[v], f[u] + 1);
            --indeg[v];
            if (!indeg[v]) {
                q.push(v);
            }
        }
        // 计算最大环
        int ring = 0, total = 0;
        for (int i = 0; i < n; ++i) {
            if (!used[i]) {
                int j = favorite[i];
                if (i == favorite[j]) {
                    total += f[i] + f[j];
                    used[i] = used[j] = 1;
                } else {
                    int u = i, cnt = 0;
                    while (1) {
                        ++cnt;
                        u = favorite[u];
                        used[u] = 1;
                        if (i == u) {
                            break;
                        }
                    }
                    ring = max(ring, cnt);
                }
            }
        }
        return max(ring, total);
    }
};

int main() {
    vector<int> favorite { 3, 0, 1, 4, 1 };
    cout << Solution().maximumInvitations(favorite) << endl;
    return 0;
}