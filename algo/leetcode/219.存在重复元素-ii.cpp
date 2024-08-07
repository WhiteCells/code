#include "../head_file.h"
/*
 * @lc app=leetcode.cn id=219 lang=cpp
 *
 * [219] 存在重复元素 II
 *
 * https://leetcode.cn/problems/contains-duplicate-ii/description/
 *
 * algorithms
 * Easy (45.21%)
 * Likes:    670
 * Dislikes: 0
 * Total Accepted:    266K
 * Total Submissions: 587.8K
 * Testcase Example:  '[1,2,3,1]\n3'
 *
 * 给你一个整数数组 nums 和一个整数 k ，判断数组中是否存在两个 不同的索引 i 和 j ，满足 nums[i] == nums[j] 且
 * abs(i - j) <= k 。如果存在，返回 true ；否则，返回 false 。
 *
 *
 *
 * 示例 1：
 *
 *
 * 输入：nums = [1,2,3,1], k = 3
 * 输出：true
 *
 * 示例 2：
 *
 *
 * 输入：nums = [1,0,1,1], k = 1
 * 输出：true
 *
 * 示例 3：
 *
 *
 * 输入：nums = [1,2,3,1,2,3], k = 2
 * 输出：false
 *
 *
 *
 *
 *
 * 提示：
 *
 *
 * 1 <= nums.length <= 10^5
 * -10^9 <= nums[i] <= 10^9
 * 0 <= k <= 10^5
 *
 *
 */

// @lc code=start
class Solution {
public:
    bool containsNearbyDuplicate(vector<int> &nums, int k) {
        unordered_map<int, set<int>> mp;
        for (int i = 0; i < nums.size(); ++i) {
            if (mp.count(nums[i])) {
                auto it = mp[nums[i]].lower_bound(i - k);
                if (it != mp[nums[i]].end()
                    && *it <= i + k) {
                    return true;
                }
            }
            mp[nums[i]].insert(i);
        }
        return false;
    }
};
// @lc code=end


int main() {
    vector<int> nums {1, 2, 3, 1, 2, 3};
    Solution s;
    cout << s.containsNearbyDuplicate(nums, 2) << endl;
    return 0;
}