#include "../../head_file.h"

/*
problme: 2874. 有序三元组中的最大值 II

给你一个下标从 0 开始的整数数组 nums 。

请你从所有满足 i < j < k 的下标三元组 (i, j, k) 中，找出并返回下标三元组的最大值。如果所有满足条件的三元组的值都是负数，则返回 0 。

下标三元组 (i, j, k) 的值等于 (nums[i] - nums[j]) * nums[k] 。


示例 1：

输入：nums = [12,6,1,2,7]
输出：77
解释：下标三元组 (0, 2, 4) 的值是 (nums[0] - nums[2]) * nums[4] = 77 。
可以证明不存在值大于 77 的有序下标三元组。

示例 2：

输入：nums = [1,10,3,4,19]
输出：133
解释：下标三元组 (1, 2, 4) 的值是 (nums[1] - nums[2]) * nums[4] = 133 。
可以证明不存在值大于 133 的有序下标三元组。

示例 3：

输入：nums = [1,2,3]
输出：0
解释：唯一的下标三元组 (0, 1, 2) 的值是一个负数，(nums[0] - nums[1]) * nums[2] = -3 。因此，答案是 0 。


提示：

    3 <= nums.length <= 105
    1 <= nums[i] <= 106


url: https://leetcode.cn/problems/maximum-value-of-an-ordered-triplet-ii/description/
 */

// 枚举 j
// time complexity: O(n)
// spatial complexity: O(n)
class Solution1 {
public:
    long long maximumTripletValue(vector<int> &nums) {
        int n = nums.size();
        vector<int> pre_max(n);
        pre_max[0] = nums[0];
        vector<int> suf_max(n);
        suf_max[n - 1] = nums[n - 1];

        // 数组的前缀最大值
        // [1, n -  2) 从 1 开始，到 n - 3 结束
        // pre_max[i] = max(nums[i], pre_max[i - 1])
        for (int i = 1; i + 2 < n; ++i) {
            pre_max[i] = max(nums[i], pre_max[i - 1]);
        }

        // 数组的后缀最大值
        // [2, n - 2] 从 n - 2 开始，到 2
        // suf_max[k] = max(nums[k], pre_max[k + 1])
        for (int k = n - 2; k > 1; --k) {
            suf_max[k] = max(nums[k], suf_max[k + 1]);
        }

        // 枚举 j
        // [1, n - 1)
        long long res = 0;
        for (int j = 1; j + 1 < n; ++j) {
            res = max(res, (long long)(pre_max[j - 1] - nums[j]) * suf_max[j + 1]);
        }
        return res;
    }
};

// 枚举 k
// time complexity: O(n)
// spatial complexity: O(1)
class Solution2 {
public:
    long long maximumTripletValue(vector<int> &nums) {
        long long res = 0;
        int n = nums.size(), max_diff = 0, pre_max = 0;

        for (const auto &ele : nums) {
            // 将 ele 视为 nums[k]
            res = max(res, (long long)max_diff * ele);
            // 将 ele 视为 nums[j], 维护最大差
            max_diff = max(max_diff, pre_max - ele);
            // 将 ele 视为 nums[i], 维护前缀最大值
            pre_max = max(pre_max, ele);
            // 先维护 res, 保证当前维护的 res 使用的是 ele 左侧的 max_diff
            // 再维护 max_diff, 保证当前维护的 max_diff 使用的是 ele 左侧的 pre_max
        }

        return res;
    }
};

int main() {
    // vector<int> nums{ 6, 11, 12, 12, 7, 9, 2, 11, 12, 4, 19, 14, 16, 8, 16 }; // 190
    vector<int> nums{ 8, 6, 3, 13, 2, 12, 19, 5, 19, 6, 10, 11, 9 }; // 266
    // vector<int> nums{ 2, 3, 1 }; // 0
    cout << Solution1().maximumTripletValue(nums) << '\n';
    cout << Solution2().maximumTripletValue(nums) << '\n';
    return 0;
}