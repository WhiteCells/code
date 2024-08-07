#include "../../head_file.h"

/*
 * @Author: Eorys
 * @Date: 2023-07-23 09:13:43
 * @Last Modified by: Eorys
 * @Last Modified time: 2023-07-23 09:13:43
 * @Description: https://leetcode.cn/problems/largest-element-in-an-array-after-merge-operations/
*/

class Solution {
public:
    long long maxArrayValue(vector<int>& nums) {
        int n = nums.size(); // 1 <= n <= 10^5
        long long ans = 0, cur_sum = 0;
        // 从后向前遍历，贪心
        for (int i = n - 1; i >= 0; --i) {
            // 当前值 <= 后边的最大元素和 当前值计入 cur_sum
            if (nums[i] <= cur_sum) {
                cur_sum += nums[i];
            }
            // 当前值 > 后边的最大元素和 更新 cur_sum 为当前元素
            else {
                cur_sum = nums[i];
            }
            // 更新 ans
            ans = max(ans, cur_sum);
        }
        return ans;
    }
};


int main() {
    Solution s;
    // auto nums = vector<int>{ 2, 3, 7, 9, 3 };
    // auto nums = vector<int>{ 5, 3, 3 };
    auto nums = vector<int>{ 91, 50 };
    cout << s.maxArrayValue(nums);
    return 0;
}