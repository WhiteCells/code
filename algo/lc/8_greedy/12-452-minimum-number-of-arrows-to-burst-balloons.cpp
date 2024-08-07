#include "D:/distake/Coding/head_file.h"

/*
 * @Author: WhiteCells
 * @Date: 2023-05-25 20:20:23
 * @Last Modified by: WhiteCells
 * @Last Modified time: 2023-05-25 20:20:23
 * @Description: 452. 用最少数量的箭引爆气球
 * https://leetcode.cn/problems/minimum-number-of-arrows-to-burst-balloons/
 * 输入：points = [[10,16],[2,8],[1,6],[7,12]]
 * 输出：2
*/

class Solution {
private:
    static bool cmp(const vector<int>& a, const vector<int>& b) {
        return a[0] < b[0];
    }
public:
    int findMinArrowShots(vector<vector<int>>& points) {
        sort(points.begin(), points.end(), cmp);
        int cnt = 1; // 统计需要的箭
        for (int i = 1; i < points.size(); ++i) {
            if (points[i][0] > points[i - 1][1]) { // 当前气球和上一个气球没有公共区间也无交点
                ++cnt;
            }
            else {
                points[i][1] = min(points[i][1], points[i - 1][1]); // 更新公共区间的最小边界
            }
        }
        return cnt;
    }
};


int main() {
    Solution s;
    // vector<vector<int>> points { {10, 16}, { 2, 8 }, { 1, 6 }, { 7, 12 } };
    // vector<vector<int>> points { {1, 2}, { 3, 4 }, { 5, 6 }, { 7, 8 } };
    vector<vector<int>> points {{1, 2}, { 2, 3 }, { 3, 4 }, { 4, 5 }};
    cout << s.findMinArrowShots(points);
    return 0;
}