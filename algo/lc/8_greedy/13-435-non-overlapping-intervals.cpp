#include "D:/distake/Coding/head_file.h"

/*
 * @Author: WhiteCells
 * @Date: 2023-05-26 21:47:53
 * @Last Modified by: WhiteCells
 * @Last Modified time: 2023-05-26 21:47:53
 * @Description: 435. 无重叠区间
 * https://leetcode.cn/problems/non-overlapping-intervals/
 * 输入: intervals = [[1,2],[2,3],[3,4],[1,3]]
 * 输出: 1
 * 解释: 移除 [1,3] 后，剩下的区间没有重叠。
*/

class Solution {
private:
    static bool cmp(const vector<int>& a, const vector<int>& b) {
        return a[1] < b[1];
    }
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end(), cmp);
        int cnt = 0; // 统计需要移除的区间个数
        for (int i = 1; i < intervals.size(); ++i) {
            if (intervals[i][0] < intervals[i - 1][1]) {
                ++cnt;
                intervals[i][1] = intervals[i - 1][1];
            }
        }
        return cnt;
    }
};

int main() {
    Solution s;
    // vector<vector<int>> intervals {{1, 2}, { 2, 3 }, { 3, 4 }, { 1, 3 }};
    // vector<vector<int>> intervals {{1, 2}, { 1, 2 }, { 1, 2 }};
    // vector<vector<int>> intervals {{1, 2}, { 2, 3 }};
    vector<vector<int>> intervals {{1, 100}, { 11, 22 }, { 1, 11 }, { 2, 12 }};
    cout << s.eraseOverlapIntervals(intervals);
    return 0;
}