// https://leetcode.cn/problems/longest-even-odd-subarray-with-threshold/

// 给你一个下标从 0 开始的整数数组 nums 和一个整数 threshold 。

// 请你从 nums 的子数组中找出以下标 l 开头、下标 r 结尾 (0 <= l <= r < nums.length) 且满足以下条件的 最长子数组 ：

//     nums[l] % 2 == 0
//     对于范围 [l, r - 1] 内的所有下标 i ，nums[i] % 2 != nums[i + 1] % 2
//     对于范围 [l, r] 内的所有下标 i ，nums[i] <= threshold

// 以整数形式返回满足题目要求的最长子数组的长度。


// 1 <= nums.length <= 100
// 1 <= nums[i] <= 100
// 1 <= threshold <= 100


// 注意：子数组 是数组中的一个连续非空元素序列。

// 输入：nums = [3,2,5,4], threshold = 5
// 输出：3
// 解释：在这个示例中，我们选择从 l = 1 开始、到 r = 3 结束的子数组 => [2,5,4] ，满足上述条件。
// 因此，答案就是这个子数组的长度 3 。可以证明 3 是满足题目要求的最大长度。


#include "../../head_file.h"

class Solution {
public:
    int longestAlternatingSubarray(vector<int>& nums, int threshold) {
        int max_len = INT32_MIN;
        int cur_len = 0;
        for (int i = 0; i + 1 < nums.size(); ++i) {
            if (0 == nums[i] % 2 && nums[i] <= threshold) {
                cur_len++;
                while (nums[i] % 2 != nums[i + 1] % 2 && nums[i + 1] <= threshold && nums[i] <= threshold && i + 1 < nums.size()) {
                    cur_len++;
                    i++;
                }
                max_len = max(max_len, cur_len);
                i++;
            }
        }
        return max_len;
    }
};


class Solution3 {
public:
    int longestAlternatingSubarray(vector<int>& nums, int threshold) {
        int ans = 0;
        int i = 0;
        int n = nums.size();
        while (i < n) {
            if (!(nums[i] & 1) || nums[i] > threshold) {
                i++; // 第一个数是 奇数 或者 大于 threshold 直接看下一个数
                continue;
            }
            int j = i; // 第一个数是 偶数 开始记录下标
            i++;
            while (i < n && ((nums[i] ^ nums[i - 1]) & 1) && nums[i] <= threshold) {
                i++;
            }
            ans = max(ans, i - j);
        }
        return ans;
    }
};


int main() {
    Solution3 s;
    vector<int> nums{ 3, 2, 5, 4 };
    // vector<int> nums{ 2, 3, 4, 5 };

    cout << s.longestAlternatingSubarray(nums, 5);
    // cout << s.longestAlternatingSubarray(nums, 4);
    return 0;
}