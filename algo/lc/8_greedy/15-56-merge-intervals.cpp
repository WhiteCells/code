#include "D:/distake/Coding/head_file.h"

/*
 * @Author: WhiteCells
 * @Date: 2023-05-28 18:31:51
 * @Last Modified by: WhiteCells
 * @Last Modified time: 2023-05-28 18:31:51
 * @Description: 56. 合并区间
 * https://leetcode.cn/problems/merge-intervals/
 * 输入：intervals = [[1,3],[2,6],[8,10],[15,18]]
 * 输出：[[1,6],[8,10],[15,18]]
 * 解释：区间 [1,3] 和 [2,6] 重叠, 将它们合并为 [1,6].
*/

class Solution {
private:
    static bool cmp(const vector<int>& a, const vector<int>& b) {
        if (a[0] == b[0]) { // 左区间相等，右区间递减（左区间相等的两个区间，后一个区间不用考虑）
            return a[1] > b[1];
        }
        return a[0] < b[0]; // 左区间递增
    }
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end(), cmp);
        int left = intervals[0][0];
        int right = intervals[0][1];
        vector<vector<int>> res {{left, right}};
        // 不应该和上一次的进行比较应该和最大的右边界进行比较
        for (int i = 1, j = 0; i < intervals.size(); ++i) {
            if (intervals[i][0] == intervals[i - 1][0]) {
                continue; // 左区间相等的两个区间，后一个区间不用考虑，因为已经排好序了
            }
            if (intervals[i][0] <= right) { // 需要合并
                res[j][1] = max(right, intervals[i][1]); // 修改右区间
            }
            else { // 不需要合并
                res.push_back(intervals[i]);
                right = intervals[i][1];
                ++j;
            }
        }
        return res;
    }
};

class Solution2 {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        vector<vector<int>> res;
        sort(intervals.begin(), intervals.end(), [](const vector<int>& a, const vector<int>& b) {return a[0] < b[0];});
        res.push_back(intervals[0]); // 第一个区间
        for (int i = 1; i < intervals.size(); ++i) {
            if (intervals[i][0] <= res.back()[1]) { // 合并区间
                res.back()[1] = max(res.back()[1], intervals[i][1]);
            }
            else { // 不需要合并
                res.push_back(intervals[i]);
            }
        }
        return res;
    }
};


int main() {
    Solution s;
    // vector<vector<int>> intervals {{1, 3}, { 2, 6 }, { 8, 10 }, { 15, 18 }};
    vector<vector<int>> intervals {{1, 4}, { 4, 5 }};
    // vector<vector<int>> intervals {{1, 4}, { 2, 3 }};
    vector<vector<int>> res = s.merge(intervals);
    for (auto& v : res) {
        for (auto& val : v) {
            cout << val << " ";
        }
        cout << '\n';
    }
    return 0;
}