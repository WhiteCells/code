#include "../../head_file.h"

/*
problme: 

url: https://leetcode.cn/problems/minimum-sum-of-mountain-triplets-ii/description/
 */

// time complexity: O()
// spatial complexity: O()
class Solution {
public:
    int minimumSum(vector<int>& nums) {
        int n = nums.size(), res = INT_MAX;
        int left_min = nums[0];
        int right_min[n];
        right_min[n - 1] = nums[n - 1];
        for (int i = n - 2; i > 0; --i) { // (0) <- (n - 2)
            right_min[i] = min(right_min[i + 1], nums[i]);
        }
        // 遍历 j
        for (int j = 1; j < n - 1; ++j) { // 1 -> n - 2
            left_min = min(left_min, nums[j - 1]);
            if (nums[j] > left_min && nums[j] > right_min[j + 1]) {
                res = min(res, left_min + nums[j] + right_min[j + 1]);
            }
        }
        return INT_MAX == res ? -1 : res;
    }
};

int main() {
    
    return 0;
}