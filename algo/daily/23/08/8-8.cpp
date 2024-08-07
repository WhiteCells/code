#include <iostream>
#include <vector>

using namespace std;
// https://leetcode.cn/problems/maximum-absolute-sum-of-any-subarray/

// 输入：nums = [1,-3,2,3,-4]
// 输出：5
// 解释：子数组 [2,3] 和的绝对值最大，为 abs(2+3) = abs(5) = 5 。

// 前缀和
class Solution {
public:
    int maxAbsoluteSum(vector<int>& nums) {
        int mx = 0, mn = 0, cur = 0;
        for (const auto& num : nums) {
            cur += num;
            if (cur > mx) {
                mx = cur;
            }
            else if (cur < mn) {
                mn = cur;
            }
        }
        return mx - mn;
    }
};

// 
class Solution2 {
public:
    int maxAbsoluteSum(vector<int>& nums) {
        int min_sum = 0, max_sum = 0, mx = 0, mn = 0;
        for (const auto& num : nums) {
            min_sum += num;
            max_sum += num;
            if (min_sum > 0) {
                min_sum = 0;
            }
            mn = min(mn, min_sum);
            if (max_sum < 0) {
                max_sum = 0;
            }
            mx = max(mx, max_sum);
        }
        return mx > abs(mn) ? mx : abs(mn);
    }
};

int main() {
    Solution2 s;
    vector<int> nums { 1, -3, 2, 3, -4 };
    cout << s.maxAbsoluteSum(nums) << '\n';
    return 0;
}