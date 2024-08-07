#include "D:/distake/Coding/head_file.h"

/*
 * @Author: WhiteCells
 * @Date: 2023-06-28 10:07:49
 * @Last Modified by: WhiteCells
 * @Last Modified time: 2023-06-28 10:07:49
 * @Description: 494. 目标和
 * https://leetcode.cn/problems/target-sum/
 *
// 输入：nums = [1,1,1,1,1], target = 3
// 输出：5
// 解释：一共有 5 种方法让最终目标和为 3 。
// -1 + 1 + 1 + 1 + 1 = 3
// +1 - 1 + 1 + 1 + 1 = 3
// +1 + 1 - 1 + 1 + 1 = 3
// +1 + 1 + 1 - 1 + 1 = 3
// +1 + 1 + 1 + 1 - 1 = 3
*/

class Solution {
private:
    vector<int> path;
    vector<vector<int>> res;
    void dfs(vector<int>& nums, int target, int start, int sum) {
        if (sum == target) {
            res.push_back(path);
        }
        for (int i = start; i < nums.size() && sum + nums[i] <= target; ++i) {
            sum += nums[i];
            path.push_back(nums[i]);
            dfs(nums, target, i + 1, sum);
            sum -= nums[i];
            path.pop_back();
        }
    }
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        int sum = 0;
        for (const auto& val : nums) {
            sum += val;
        }
        if (target > sum) {
            return -1;
        }
        int bag_size = (sum + target) / 2;
        if (bag_size % 2) {
            return -1;
        }
        sort(nums.begin(), nums.end());
        dfs(nums, bag_size, 0, 0);
        return res.size();
    }
};

class Solution2 {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        int sum = 0;  // 最大的总和
        for (const auto& num : nums) {
            sum += num;
        }
        if ((sum + target) % 2) {
            return 0;
        }
        // 目标值的绝对值比总值大，就不可能组成目标值
        if (abs(target) > sum) {
            return 0;
        }
        int bag_size = (sum + target) / 2;
        int dp[bag_size + 1] = { 0 };
        dp[0] = 1;
        for (int i = 0; i < nums.size(); ++i) {
            for (int j = bag_size; j >= nums[i]; --j) {
                dp[j] += dp[j - nums[i]];
            }
        }
        return dp[bag_size];
    }
};


int main() {
    Solution2 s;
    vector<int> nums{ 1, 1, 1, 1, 1 };
    int target = 3;
    cout << s.findTargetSumWays(nums, target) << '\n';
    return 0;
}