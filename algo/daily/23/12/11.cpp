#include "../../head_file.h"

/*
problme:

url:
 */

class Solution {
public:
    int minimumEffortPath(vector<vector<int>> &heights) {
        int m = heights.size(), n = heights[0].size(), cnt = m * n;
        auto cmp = [](const auto &e1, const auto &e2) {
            auto &&[x1, y1, d1] = e1;
            auto &&[x2, y2, d2] = e2;
            return d1 > d2;
        };
        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, decltype(cmp)> q(cmp);
        q.emplace(0, 0, 0);
        vector<int> dist(cnt, INT_MAX);
        dist[0] = 0;
        vector<int> seen(cnt);
        while (!q.empty()) {
            auto [x, y, d] = q.top();
            q.pop();
            int id = x * n + y;
            if (seen[id]) {
                continue;
            }
            if (x == m - 1 && y == n - 1) {
                break;
            }
            seen[id] = 1;
            for (int i = 0; i < 4; ++i) {
                int nx = x + dir[i][0];
                int ny = y + dir[i][1];
                if (nx >= 0 && nx < m && ny >= 0 && ny < n
                    && max(d, abs(heights[x][y] - heights[nx][ny])) < dist[nx * n + ny]) {
                    dist[nx * n + ny] = max(d, abs(heights[x][y] - heights[nx][ny]));
                    q.emplace(nx, ny, dist[nx * n + ny]);
                }
            }
        }
        return dist[cnt - 1];
    }
private:
    static constexpr int dir[4][2] {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
};

int main() {
    vector<vector<int>> v {
        {1, 2, 3},
        {3, 8, 2},
        {5, 3, 5},
    };
    cout << Solution().minimumEffortPath(v) << endl;
    return 0;
}