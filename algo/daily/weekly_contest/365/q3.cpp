#include "../../head_file.h"

/*
problme: 2875. 无限数组的最短子数组

给你一个下标从 0 开始的数组 nums 和一个整数 target 。

下标从 0 开始的数组 infinite_nums 是通过无限地将 nums 的元素追加到自己之后生成的。

请你从 infinite_nums 中找出满足 元素和 等于 target 的 最短 子数组，并返回该子数组的长度。如果不存在满足条件的子数组，返回 -1 。


示例 1：

输入：nums = [1,2,3], target = 5
输出：2
解释：在这个例子中 infinite_nums = [1,2,3,1,2,3,1,2,...] 。
区间 [1,2] 内的子数组的元素和等于 target = 5 ，且长度 length = 2 。
可以证明，当元素和等于目标值 target = 5 时，2 是子数组的最短长度。

示例 2：

输入：nums = [1,1,1,2,3], target = 4
输出：2
解释：在这个例子中 infinite_nums = [1,1,1,2,3,1,1,1,2,3,1,1,...].
区间 [4,5] 内的子数组的元素和等于 target = 4 ，且长度 length = 2 。
可以证明，当元素和等于目标值 target = 4 时，2 是子数组的最短长度。

示例 3：

输入：nums = [2,4,6,8], target = 3
输出：-1
解释：在这个例子中 infinite_nums = [2,4,6,8,2,4,6,8,...] 。
可以证明，不存在元素和等于目标值 target = 3 的子数组。


提示：

    1 <= nums.length <= 105
    1 <= nums[i] <= 105
    1 <= target <= 109

url: https://leetcode.cn/problems/minimum-size-subarray-in-infinite-array/description/
 */


// time complexity: O(n)
// spatial complexity: O(n)
// 从 target 中去掉若干个 sum(nums), 剩余元素之和为 target % sum(nums)
// 剩余元素的个数 < n
// 只需要在 nums + nums 中找最短子数组之和等于剩余元素的之和 target % sum(nums) 的长度加上 target / sum(nums) * n
class Solution1 {
public:
    int minSizeSubarray(vector<int> &nums, int target) {
        long long sum = 0LL;
        for (const auto &ele : nums) {
            sum += ele;
        }
        int n = nums.size();
        int m = target / sum * n; // 需要的若干个 nums 的长度
        target %= sum; // 新目标值
        vector<int> two_nums;
        for (int i = 0; i < 2; ++i) {
            for (const auto &ele : nums) {
                two_nums.emplace_back(ele);
            }
        }
        int res = INT_MAX, left = 0, right = 0, cur = 0;
        while (right < n * 2) {
            cur += two_nums[right];
            while (cur > target) {
                cur -= two_nums[left++];
            }
            if (cur == target) {
                res = min(res, right - left + 1);
            }
            ++right;
        }
        return INT_MAX == res ? -1 : res + m;
    }
};

// time complexity: O(n)
// spatial complexity: O(1)
// 在原数组上操作
class Solution2 {
public:
    int minSizeSubarray(vector<int> &nums, int target) {
        long long sum = 0;
        for (const auto &ele : nums) {
            sum += ele;
        }
        int n = nums.size();
        int m = target / sum * n; // 需要的若干个 nums 的长度
        target %= sum; // 新的目标
        int res = INT_MAX, left = 0, right = 0, cur = 0;
        while (right < n * 2) {
            cur += nums[right % n];
            while (cur > target) {
                cur -= nums[left % n];
                ++left;
            }
            if (cur == target) {
                res = min(res, right - left + 1);
            }
            ++right;
        }
        return INT_MAX == res ? -1 : res + m;
    }
};

int main() {
    vector<int> nums{ 1, 1, 1, 2, 3 };
    int target = 4;
    cout << Solution1().minSizeSubarray(nums, target) << '\n';
    cout << Solution2().minSizeSubarray(nums, target) << '\n';
    return 0;
}