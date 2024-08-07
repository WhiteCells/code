#include "D:/distake/Coding/head_file.h"

/*
 * @Author: WhiteCells
 * @Date: 2023-06-12 09:53:53
 * @Last Modified by: WhiteCells
 * @Last Modified time: 2023-06-12 09:53:53
 * @Description: 416. 分割等和子集
 * https://leetcode.cn/problems/partition-equal-subset-sum/
*/

class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int sum = 0;
        // 题目中数组的长度最大为 200，每个数的大小最大 100
        vector<int> dp(10001, 0);
        for (int i = 0; i < nums.size(); ++i) {
            sum += nums[i];
        }
        int target = sum / 2;
        for (int i = 0; i < nums.size(); ++i) {
            for (int j = target; j >= nums[i]; --j) {
                dp[j] = max(dp[j], dp[j - nums[i]] + nums[i]);
            }
        }
        return dp[target] == target;
    }
};


int main() {
    Solution s;
    vector<int> nums{ 1, 5, 11, 5 };
    cout << s.canPartition(nums);
    return 0;
}