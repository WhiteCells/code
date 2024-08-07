#include <iostream>
#include <vector>
#include <queue>

using namespace std;
// https://leetcode.cn/problems/max-value-of-equation/

class Solution {
public:
    int findMaxValueOfEquation(vector<vector<int>>& points, int k) {
        deque<int> q;
        int n = points.size(), ans = -1e9;
        for (int i = 0; i < n; ++i) {
            // 维护 xj - xi > k
            while (!q.empty() && points[i][0] - points[q.front()][0] > k) {
                q.pop_front();
            }
            if (!q.empty()) {
                // yi + yj + |xi - xj|（题目中 xj > xi）
                // = yi + yj + xj - xi
                ans = max(ans, points[i][0] + points[i][1]
                    + points[q.front()][1] - points[q.front()][0]);
            }
            // 
            while (!q.empty() && points[q.back()][1] - points[q.back()][0]
                < points[i][1] - points[i][0]) {
                q.pop_back();
            }
        }
        return ans;
    }
};

int main() {
    auto points = vector<vector<int>>{ { 1, 3 }, { 2, 0 }, { 5, 10 }, { 6, -10 } };
    int k = 1;
    Solution s;
    cout << s.findMaxValueOfEquation(points, k);
    return 0;
}