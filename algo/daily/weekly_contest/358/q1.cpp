#include "../../head_file.h"

/*
problme: 6939. 数组中的最大数对和
给你一个下标从 0 开始的整数数组 nums 。请你从 nums 中找出和 最大 的一对数，且这两个数数位上最大的数字相等。
返回最大和，如果不存在满足题意的数字对，返回 -1 。
输入：nums = [51,71,17,24,42]
输出：88
解释：
i = 1 和 j = 2 ，nums[i] 和 nums[j] 数位上最大的数字相等，且这一对的总和 71 + 17 = 88 。
i = 3 和 j = 4 ，nums[i] 和 nums[j] 数位上最大的数字相等，且这一对的总和 24 + 42 = 66 。
可以证明不存在其他数对满足数位上最大的数字相等，所以答案是 88 。
数据范围：
    2 <= nums.length <= 100
    1 <= nums[i] <= 10^4
url: https://leetcode.cn/problems/max-pair-sum-in-an-array/
@Author: Eorys
@Date: 2023-08-14 08:37:00
@Last Modified by: Eorys
@Last Modified time: 2023-08-14 08:37:00
@Description:
*/


class Solution {
public:
    // 100ms
    int maxSum(vector<int>& nums) {
        unordered_map<int, int> mp; // 最大位 : 最大位的值
        for (const auto& num : nums) {
            int tmp = num, max_bit = 0;
            while (tmp) {
                max_bit = max(max_bit, tmp % 10);
                tmp /= 10;
            }
            mp[num] = max_bit;
        }
        int n = nums.size(), res = -1;
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (mp[nums[i]] == mp[nums[j]]) {
                    res = max(res, nums[j] + nums[i]);
                }
            }
        }
        return res;
    }
};

class Solution2 {
public:
    // 36ms
    int maxSum(vector<int>& nums) {
        unordered_map<int, int> mp;
        int res = -1;
        for (const auto& num : nums) {
            int tmp = num, max_bit = 0;
            while (tmp) {
                max_bit = max(max_bit, tmp % 10);
                tmp /= 10;
            }
            if (mp.find(max_bit) != mp.end()) {
                res = max(res, num + mp[max_bit]);
            }
            // max_bit 可能重复，此时更新为最大的值
            mp[max_bit] = max(mp[max_bit], num);
        }
        return res;
    }
    // 20ms
    int maxSum2(vector<int>& nums) {
        // 这里使用数组记录最大位，这里最大位只可能是 1~9
        int mp[10] {};
        int res = -1;
        for (const auto& num : nums) {
            int tmp = num, max_bit = 0;
            while (tmp) {
                max_bit = max(max_bit, tmp % 10);
                tmp /= 10;
            }
            if (mp[max_bit]) {
                res = max(res, num + mp[max_bit]);
            }
            if (num > mp[max_bit]) {
                mp[max_bit] = num;
            }
        }
        return res;
    }
};

int main() {
    vector<int> nums1 { 51, 71, 17, 24, 42 };
    vector<int> nums2 { 1, 2, 3, 4 };
    vector<int> nums3 { 84, 91, 18, 59, 27, 9, 81, 33, 17, 58 };
    vector<int> nums4 { 1094, 724, 355, 2086, 655 };

    Solution s;
    // cout << s.maxSum(nums1) << '\n';
    // cout << s.maxSum(nums2) << '\n';

    Solution2 s2;
    // cout << s2.maxSum(nums1) << '\n';
    // cout << s2.maxSum(nums2) << '\n';
    // cout << s2.maxSum(nums3) << '\n';
    // cout << s2.maxSum2(nums3) << '\n';
    return 0;
}