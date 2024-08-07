#include <iostream>
#include <vector>

using namespace std;
// https://leetcode.cn/problems/maximum-sum-circular-subarray/

class Solution {
public:
    int maxSubarraySumCircular(vector<int>& nums) {
        // 情况1 子数组是中间，数组首尾不相连
        // 情况2 子数组是两端，数组首尾相连
        // max(最大子数组和, 总和 - 最小子数组和) // 总和 - 最小子数组和 避开环
        int cur_max_sum = 0;
        int max_sum = nums[0];
        int cur_min_sum = 0;
        int min_sum = nums[0];
        int sum = 0;
        for (const auto& num : nums) {
            sum += num;
            cur_max_sum = max(cur_max_sum + num, num);
            max_sum = max(max_sum, cur_max_sum);
            cur_min_sum = min(cur_min_sum + num, num);
            min_sum = min(min_sum, cur_min_sum);
        }
        return max_sum > 0 ? max(max_sum, sum - min_sum) : max_sum;
    }
};

int main() {
    auto nums = vector<int>{ 5, -3, 5 };
    Solution s;
    cout << s.maxSubarraySumCircular(nums);
    return 0;
}