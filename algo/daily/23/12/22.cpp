#include "../../head_file.h"

/*
problme: 

url: https://leetcode.cn/problems/minimum-number-of-removals-to-make-mountain-array/description/
 */

// TODO
class Solution {
public:
    int minimumMountainRemovals(vector<int>& nums) {
        int n = nums.size();
        vector<int> pre = getLISArray(nums);
        vector<int> suf = getLISArray({nums.rbegin(), nums.rend()});
        reverse(suf.begin(), suf.end());

        int ans = 0;
        for (int i = 0; i < n; ++i) {
            if (pre[i] > 1 && suf[i] > 1) {
                ans = max(ans, pre[i] + suf[i] - 1);
            }
        }

        return n - ans;
    }

    vector<int> getLISArray(const vector<int>& nums) {
        int n = nums.size();
        vector<int> dp(n, 1);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < i; ++j) {
                if (nums[j] < nums[i]) {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
        }
        return dp;
    }
};

int main() {
    
    return 0;
}