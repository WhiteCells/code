#include "../../head_file.h"

/*
problme:

url:
*/

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        auto cmp = [&](const vector<int>& v1, const vector<int>& v2) {
            return v1[0] != v2[0] ? v1[0] < v2[0] : v1[1] < v2[1];
        };
        sort(intervals.begin(), intervals.end(), cmp);
        vector<vector<int>> res;
        res.push_back({ intervals[0][0], intervals[0][1] });
        int n = intervals.size();
        for (int i = 1; i < n; ++i) {
            int m = intervals.size();
            // 当前区间的开始 <= 上一个区间的结束，不在一个区间
            if (intervals[i][0] <= res.back()[1]) {
                // 且 当前区间的结尾 > 上一个区间的结尾
                if (intervals[i][1] > res.back()[1]) {
                    // 修改上一个区间的结尾
                    res.back()[1] = intervals[i][1];
                }
            }
            // 当前区间的开始 > 上一个区间的结束，不在一个区间
            else {
                res.push_back({ intervals[i][0], intervals[i][1] });
            }
        }
        return res;
    }
};

int main() {
    vector<vector<int>> intervals { { 1, 3 }, { 2, 6 }, { 8, 10 }, { 15, 18 } };
    Solution s;
    vector<vector<int>> res = s.merge(intervals);
    for (const auto& v : res) {
        for (const auto& elem : v) {
            cout << elem << ' ';
        }
        cout << '\n';
    }
    return 0;
}