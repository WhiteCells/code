#include "../../head_file.h"

/*
problme: 2835. 使子序列的和等于目标的最少操作次数
给你一个下标从 0 开始的数组 nums ，它包含 非负 整数，且全部为 2 的幂，同时给你一个整数 target 。

一次操作中，你必须对数组做以下修改：

    选择数组中一个元素 nums[i] ，满足 nums[i] > 1 。
    将 nums[i] 从数组中删除。
    在 nums 的 末尾 添加 两个 数，值都为 nums[i] / 2 。

你的目标是让 nums 的一个 子序列 的元素和等于 target ，请你返回达成这一目标的 最少操作次数 。如果无法得到这样的子序列，请你返回 -1 。

数组中一个 子序列 是通过删除原数组中一些元素，并且不改变剩余元素顺序得到的剩余数组。
输入：nums = [1,2,8], target = 7
输出：1
解释：第一次操作中，我们选择元素 nums[2] 。数组变为 nums = [1,2,4,4] 。
这时候，nums 包含子序列 [1,2,4] ，和为 7 。
无法通过更少的操作得到和为 7 的子序列。
提示：

    1 <= nums.length <= 1000
    1 <= nums[i] <= 230
    nums 只包含非负整数，且均为 2 的幂。
    1 <= target < 231

url: https://leetcode.cn/problems/minimum-operations-to-form-subsequence-with-target-sum/
*/

class Solution {
public:
    int minOperations(vector<int>& nums, int target) {
        long long sum = accumulate(nums.begin(), nums.end(), 0LL);
        if (sum < target) {
            return -1;
        }
        // target 表示为二进制，7 == (1 << 2) + (1 << 1) + (1 << 0)
        // 1 2 8
        // 0 0 0 1
        // 0 0 1 0
        // 1 0 0 0
        // 7
        // 0 1 1 1
        unordered_map<int, int> mp;
        for (const auto &num : nums) {
            mp[num] += 1;
        }
        // 从大到小枚举 target 中的二进制数
        for (int i = 30; i >= 0; --i) {
            int val = 1 << i;
            if (mp.count(val)) {
                target -= val; // 先减去一部分可以直接使用的，也就是大的
                if (0 == --mp[val]) {
                    mp.erase(val);
                }
            }
        }
        // 从小向到大枚举 target 中剩余的二进制位的数，先凑，不够再拆
        for (int i = 0; i <= 30; ++i) {
            if (target >> i & 1) {
                int val = 1 << i;

            }
        }

    }
};

int main() {
    // vector<int> nums { 1, 32, 1 };
    // int target = 35;
    // vector<int> nums { 1, 32, 1, 2 };
    // int target = 12;
    // vector<int> nums { 1, 2, 8 };
    // int target = 7;
    vector<int> nums { 16, 128, 32 };
    int target = 1;
    cout << Solution().minOperations(nums, target) << '\n';
    return 0;
}