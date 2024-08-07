#include "../../head_file.h"

/*
problme: 136. 只出现一次的数字

给你一个 非空 整数数组 nums ，除了某个元素只出现一次以外，其余每个元素均出现两次。找出那个只出现了一次的元素。

你必须设计并实现线性时间复杂度的算法来解决此问题，且该算法只使用常量额外空间。


示例 1 ：

输入：nums = [2,2,1]
输出：1

示例 2 ：

输入：nums = [4,1,2,1,2]
输出：4

示例 3 ：

输入：nums = [1]
输出：1


提示：

    1 <= nums.length <= 3 * 104
    -3 * 104 <= nums[i] <= 3 * 104
    除了某个元素只出现一次以外，其余每个元素均出现两次。


url: https://leetcode.cn/problems/single-number/description
 */

// time complexity: O(nlogn)
// spatial complexity: O(1)
// 排序，然后每两个一组, 组内进行比较
// 0 0 1 2 2 3 3  偶数时, 第一个只出现一次的数一定是在每一组的第一个
// 2 2 3 3 4      奇数时, 前面的每一组中的数都相等, 则最后一个数一定就是只出现一次的数
class Solution1 {
public:
    int singleNumber(vector<int> &nums) {
        sort(nums.begin(), nums.end());
        for (int i = 0; i + 1 < nums.size(); i += 2) {
            if (nums[i] != nums[i + 1]) {
                return nums[i];
            }
        }
        return nums[nums.size() - 1];
    }
};

// time complexity: O(n)
// spatial complexity: O(1)
// 使用 按位异或 XOR 相异为 1 相同为 0 的性质
// 2 3 3
// 2^3^3 = 2^0 = 2
class Solution2 {
public:
    int singleNumber(vector<int> &nums) {
        int res = 0;
        for (const auto &num : nums) {
            res ^= num;
        }
        return res;
    }
};

int main() {
    vector<int> nums { 4, 1, 2, 1, 2 };
    cout << Solution1().singleNumber(nums) << '\n';
    cout << Solution2().singleNumber(nums) << '\n';
    return 0;
}