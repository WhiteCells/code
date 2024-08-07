#include "../../head_file.h"

/*
problme: 57. 插入区间
给你一个 无重叠的 ，按照区间起始端点排序的区间列表。
在列表中插入一个新的区间，你需要确保列表中的区间仍然有序且不重叠（如果有必要的话，可以合并区间）。
输入：intervals = [[1,2],[3,5],[6,7],[8,10],[12,16]], newInterval = [4,8]
输出：[[1,2],[3,10],[12,16]]
解释：这是因为新的区间 [4,8] 与 [3,5],[6,7],[8,10] 重叠。
提示：
    0 <= intervals.length <= 10^4
    intervals[i].length == 2
    0 <= intervals[i][0] <= intervals[i][1] <= 10^5
    intervals 根据 intervals[i][0] 按 升序 排列
    newInterval.length == 2
    0 <= newInterval[0] <= newInterval[1] <= 10^5
url: https://leetcode.cn/problems/insert-interval/
*/

class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        if (intervals.empty()) {
            return {};
        }
        vector<vector<int>> res;
        int i = 0;
        bool flag = false; // 新区间有可能不存在重叠
        while (i < intervals.size()) {
            // 新区间左侧 < 当前区间的右侧，需要合并
            if (newInterval[0] <= intervals[i][1]) {
                // 新区间左侧 [3, 5] [1, 8]
                newInterval[0] = min(newInterval[0], intervals[i][0]);
                // 新区间右侧 
                newInterval[1] = max(newInterval[1], intervals[i][1]);
                // 当前区间左侧 < 新区间右侧，继续合并
                ++i;
                while (i < intervals.size() && intervals[i][0] <= newInterval[1]) {
                    // 新区间左侧
                    // newInterval[0] = min(newInterval[0], intervals[i][0]);
                    // 新区间右侧
                    newInterval[1] = max(newInterval[1], intervals[i][1]);
                    ++i;
                }
                res.push_back(newInterval);
                newInterval[0] = 1e5 + 1;
                flag = true;
            }
            else {
                res.push_back(intervals[i]);
                ++i;
            }
        }
        if (!flag) {
            res.push_back(newInterval);
        }
        return res;
    }
};

class Solution2 {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        if (intervals.empty()) {
            return { newInterval };
        }
        intervals.push_back(newInterval);
        auto cmp = [&](const vector<int>& v1, const vector<int>& v2) {
            return v1[0] < v2[0];
        };
        sort(intervals.begin(), intervals.end(), cmp);
        vector<vector<int>> res;
        res.push_back(intervals[0]);
        for (int i = 1; i < intervals.size(); ++i) {
            // 当前区间的左侧 <= 上一个区间的右侧
            if (intervals[i][0] <= res.back()[1]) {
                // 修改上一个区间的右侧
                res.back()[1] = max(res.back()[1], intervals[i][1]);
            }
            else {
                res.push_back(intervals[i]);
            }
        }
        return res;
    }
};

int main() {
    vector<vector<int>> intervals { { 1, 2 }, { 3, 5 }, { 6, 7 }, { 8, 10 }, { 12, 16 } };
    vector<int> new_interval { 4, 8 };
    Solution2 s;
    vector<vector<int>> res = s.insert(intervals, new_interval);
    for (const auto& v : res) {
        for (const auto& ele : v) {
            cout << ele << ' ';
        }
        cout << '\n';
    }
    return 0;
}