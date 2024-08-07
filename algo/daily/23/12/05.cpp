#include "../../head_file.h"

/*
problme:

url:
 */

class Solution {
public:
    long long minimumFuelCost(vector<vector<int>> &roads, int seats) {
        vector<vector<int>> g(roads.size() + 1);
        for (const auto &e : roads) {
            int x = e[0], y = e[1];
            g[x].push_back(y);
            g[y].push_back(x);
        }
        long long res = 0;
        // 统计子树的长度
        function<int(int, int)> dfs = [&](int x, int f) -> int {
            int size = 1;
            // 递归所有终点
            for (const auto &y : g[x]) {
                // 终点不为父节点时
                if (y != f) {
                    // 以终点为起点，起点为父节点，继续递归
                    size += dfs(y, x);
                }
            }
            // 当前子树根节点不是首都
            if (x) {
                // 贪心，当前子树长度除以座位，向上取整
                res += (size - 1) / seats + 1;
            }
            return size;
        };
        dfs(0, -1);
        return res;
    }
};

int main() {
    vector<vector<int>> roads {
        {0, 1},
        {0, 2},
        {0, 3},
    };
    int seats = 5;
    cout << Solution().minimumFuelCost(roads, seats) << endl;
    return 0;
}