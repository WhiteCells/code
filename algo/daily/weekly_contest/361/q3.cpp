#include "../../head_file.h"

/*
problme: 2845. 统计趣味子数组的数目
给你一个下标从 0 开始的整数数组 nums ，以及整数 modulo 和整数 k 。

请你找出并统计数组中 趣味子数组 的数目。

如果 子数组 nums[l..r] 满足下述条件，则称其为 趣味子数组 ：

    在范围 [l, r] 内，设 cnt 为满足 nums[i] % modulo == k 的索引 i 的数量。并且 cnt % modulo == k 。

以整数形式表示并返回趣味子数组的数目。

注意：子数组是数组中的一个连续非空的元素序列。

示例 2：

输入：nums = [3,1,9,6], modulo = 3, k = 0
输出：2
解释：在这个示例中，趣味子数组分别是：
子数组 nums[0..3] ，也就是 [3,1,9,6] 。
- 在范围 [0, 3] 内，只存在 3 个下标 i = 0, 2, 3 满足 nums[i] % modulo == k 。
- 因此 cnt = 3 ，且 cnt % modulo == k 。
子数组 nums[1..1] ，也就是 [1] 。
- 在范围 [1, 1] 内，不存在下标满足 nums[i] % modulo == k 。
- 因此 cnt = 0 ，且 cnt % modulo == k 。
可以证明不存在其他趣味子数组，因此答案为 2 。

提示：

    1 <= nums.length <= 105
    1 <= nums[i] <= 109
    1 <= modulo <= 109
    0 <= k < modulo

url: https://leetcode.cn/problems/count-of-interesting-subarrays/
 */
/*
    3 1 9 6 modulo = 3 k = 0
    1 0 1 1

    1 0 1 1
    0
 */

/*
    前缀和，子数组求和
 */
/*
    (x - y) % mod = x % mod - y % mod 存在问题

    (6 - 5) % 3 = 1
    6 % 3 - 5 % 3 = 0 - 2 = -2

    结果负数需要再 + mod
    (x - y) % mod = x % mod - y % mod + mod
    结果非负
    (x - y) % mod = x % mod - y % mod

    (x - y) % mod = (x % mod - y % mod + mod) % mod

 */
class Solution {
public:
    long long countInterestingSubarrays(vector<int> &nums, int modulo, int k) {
        vector<int> v;
        /*
            前缀和
            index:    0 1 2 3
            value:    0 1 5 3
            pradd:  0 0 1 6 9

            sum([0, 2]) = 6 - 0
            sum([2, 3]) = 9 - 1
            sum([1, 3]) = 9 - 0
        */
        vector<int> pre_and { 0 };
        /* 前缀和 */
        for (const auto &ele : nums) {
            /* nums[i] % modulo == k => nums[i] = 1 */
            pre_and.emplace_back(pre_and.back() + (k == ele % modulo));
        }
        /* 两数之差 */
        unordered_map<int, int> cnt;
        long long res = 0;
        for (const auto &ele : pre_and) {
            // (pre[R] % mod - pre[L] % mod + mod) % mod == k
            // pre[L] % mod == (pre[R] % mod - k + mod) % mod // 知道右找左
            // res += cnt.count((ele % modulo - k % modulo + modulo) % modulo); // count 只能统计 key
            res += cnt[(ele % modulo - k % modulo + modulo) % modulo];
            ++cnt[ele % modulo];
        }
        return res;
    }
};

/*
优化前缀和
 */
class Solution2 {
public:
    long long countInterestingSubarrays(vector<int> &nums, int modulo, int k) {
        unordered_map<int, int> cnt;
        cnt[0] = 1; // 前缀和，0 也要出现一次
        int pre = 0;
        long long res = 0;
        for (const auto &ele : nums) {
            pre += (k == ele % modulo); // 更新当前前缀和
            res += cnt[(pre % modulo - k % modulo + modulo) % modulo];
            ++cnt[pre % modulo];
        }
        return res;
    }
};

int main() {
    // auto nums = vector<int> { 3, 1, 9, 6 };
    // int modulo = 3, k = 0;

    auto nums = vector<int> { 11, 12, 21, 31 };
    int modulo = 10, k = 1;
    cout << Solution().countInterestingSubarrays(nums, modulo, k) << '\n';
    cout << Solution2().countInterestingSubarrays(nums, modulo, k) << '\n';

    return 0;
}