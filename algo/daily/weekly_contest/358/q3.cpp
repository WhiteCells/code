#include "../../head_file.h"

/*
problme: 2817. 限制条件下元素之间的最小绝对差
给你一个下标从 0 开始的整数数组 nums 和一个整数 x 。
请你找到数组中下标距离至少为 x 的两个元素的 差值绝对值 的 最小值 。
换言之，请你找到两个下标 i 和 j ，满足 abs(i - j) >= x 且 abs(nums[i] - nums[j]) 的值最小。
请你返回一个整数，表示下标距离至少为 x 的两个元素之间的差值绝对值的 最小值 。
输入：nums = [4,3,2,4], x = 2
输出：0
解释：我们选择 nums[0] = 4 和 nums[3] = 4 。
它们下标距离满足至少为 2 ，差值绝对值为最小值 0 。
0 是最优解。
提示：
    1 <= nums.length <= 10^5
    1 <= nums[i] <= 10^9
    0 <= x < nums.length
url: https://leetcode.cn/problems/minimum-absolute-difference-between-elements-with-constraint/
@Author: Eorys
@Date: 2023-08-14 21:10:50
@Last Modified by: Eorys
@Last Modified time: 2023-08-14 21:10:50
@Description:
*/

class Solution {
public:
    int minAbsoluteDifference(vector<int>& nums, int x) {
        set<int> s { INT_MIN / 2, INT_MAX }; // 保证 lower_bound 存在，INT_MIN / 2 防止溢出
        int res = INT_MAX;
        // for (int i = 0, j = i + x; j < nums.size(); ++i, ++j) {
        //     s.insert(nums[i]);
        //     auto it = s.lower_bound(nums[j]);
        //     // res = min(res, min(abs(nums[j] - *it), abs(nums[j] - *(--it))));
        //     res = min(res, min(*it - nums[j], nums[j] - *(--it)));
        // }
        for (int i = x; i < nums.size(); ++i) {
            s.insert(nums[i - x]);
            auto it = s.lower_bound(nums[i]);
            res = min(res, min(abs(*it - nums[i]), abs(nums[i] - *--it)));
        }
        return res;
    }
};

class Solution2 {
public:
    int minAbsoluteDifference(vector<int>& nums, int x) {
        set<int> s { INT_MIN / 2, INT_MAX };
        int res = INT_MAX;
        for (int i = x; i < nums.size(); ++i) {
            s.insert(nums[i - x]);
            auto it = s.lower_bound(nums[i]);
            int val1 = nums[i] - *it;
            int val2 = nums[i] - *--it; // 不存在比当前值大的情况
            // res = min(res, min(abs(nums[i] - *it), abs(nums[i] - *--it)));
            res = min(res, min(abs(val1), abs(val2)));
        }
        return res;
    }
};

int main() {
    Solution2 s;

    // vector<int> nums { 5, 3, 2, 10, 15 };
    // int x = 1;
    vector<int> nums { 4, 3, 2, 4 };
    int x = 2;
    // vector<int> nums { 74, 4 };
    // int x = 1;

    cout << s.minAbsoluteDifference(nums, x);
    return 0;
}