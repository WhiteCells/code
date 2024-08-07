#include "D:/distake/Coding/head_file.h"

/*
 * @Author: WhiteCells
 * @Date: 2023-05-17 21:39:24
 * @Last Modified by: WhiteCells
 * @Last Modified time: 2023-05-17 21:39:24
 * @Description: 376-摆动序列
 * https://leetcode.cn/problems/wiggle-subsequence/
 * [1,7,4,9,2,5]
*/

class Solution {
public:
    int wiggleMaxLength(vector<int>& nums) {
        int count = 1;   // 统计峰值（最右边有一个峰值）
        int curDiff = 0; // 当前一对差值
        int preDiff = 0; // 之前一对差值
        for (int i = 0; i + 1 < nums.size(); ++i) {
            curDiff = nums[i + 1] - nums[i];
            if (curDiff > 0 && preDiff <= 0 || curDiff < 0 && preDiff >= 0) {
                ++count;
                preDiff = curDiff;
            }
        }
        return count;
    }
};

int main() {
    Solution s;
    vector<int> nums {3, 3, 3, 2, 5};
    cout << s.wiggleMaxLength(nums);
    return 0;
}