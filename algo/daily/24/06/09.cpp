#include "../../head_file.h"

/*
problme:

url: https://leetcode.cn/problems/burst-balloons/
 */

class Solution {
public:
    int maxCoins(vector<int> &nums) {
        nums.insert(nums.begin(), 1);
        nums.insert(nums.end(), 1);

        int n = nums.size();
        vector<vector<int>> dp(n, vector<int>(n, 0));

        /// @brief 区间 (i, j) 内枚举 k
        /// @param i 左开区间
        /// @param j 右开区间
        auto helper = [&](int i, int j) {
            int res = dp[i][j];
            for (int k = i + 1; k < j; ++k) {
                int left = dp[i][k];
                int mid = nums[i] * nums[k] * nums[j];
                int right = dp[k][j];
                res = max(res, left + mid + right);
            }
            dp[i][j] = res;
        };

        for (int len = 3; len < n + 1; ++len) {
            for (int i = 0; i + len < n + 1; ++i) {
                helper(i, i + len - 1);
            }
        }
        return dp[0][n - 1];
    }
};

int main() {
    vector<int> nums {3,1,5,8};
    cout << Solution().maxCoins(nums) << endl;
    return 0;
}