#include "../../head_file.h"

/*
problme:

url: https://leetcode.cn/problems/maximum-sum-of-3-non-overlapping-subarrays/?envType=daily-question&envId=2023-11-19
 */

// time complexity: O()
// spatial complexity: O()
class Solution {
public:
    vector<int> maxSumOfThreeSubarrays(vector<int> &nums, int k) {
        const size_t n = nums.size();
        long sum[n + 1] {};
        for (int i = 1; i <= n; ++i) {
            sum[i] = sum[i - 1] + nums[i - 1];
        }
        long mp[n + 10][4] {};
        for (int i = n - k + 1; i >= 1; --i) {
            for (int j = 1; j < 4; ++j) {
                mp[i][j] = max(mp[i + 1][j], mp[i + k][j - 1] + sum[i + k - 1] - sum[i - 1]);
            }
        }
        vector<int> res(3);
        int i = 1, j = 3, idx = 0;
        while (j > 0) {
            if (mp[i + 1][j] > mp[i + k][j - 1]
                + sum[i + k - 1] - sum[i - 1]) {
                ++i;
            } else {
                res[idx++] = i - 1;
                i += k;
                --j;
            }
        }
        return res;
    }
};

class Solution2 {
public:
    vector<int> maxSumOfThreeSubarrays(vector<int> &nums, int k) {
        vector<int> ans;
        int sum1 = 0, maxSum1 = 0, maxSum1Idx = 0;
        int sum2 = 0, maxSum12 = 0, maxSum12Idx1 = 0, maxSum12Idx2 = 0;
        int sum3 = 0, maxTotal = 0;
        for (int i = k * 2; i < nums.size(); ++i) {
            sum1 += nums[i - k * 2];
            sum2 += nums[i - k];
            sum3 += nums[i];
            if (i >= k * 3 - 1) {
                if (sum1 > maxSum1) {
                    maxSum1 = sum1;
                    maxSum1Idx = i - k * 3 + 1;
                }
                if (maxSum1 + sum2 > maxSum12) {
                    maxSum12 = maxSum1 + sum2;
                    maxSum12Idx1 = maxSum1Idx;
                    maxSum12Idx2 = i - k * 2 + 1;
                }
                if (maxSum12 + sum3 > maxTotal) {
                    maxTotal = maxSum12 + sum3;
                    ans = { maxSum12Idx1, maxSum12Idx2, i - k + 1 };
                }
                sum1 -= nums[i - k * 3 + 1];
                sum2 -= nums[i - k * 2 + 1];
                sum3 -= nums[i - k + 1];
            }
        }
        return ans;
    }
};

int main() {
    vector<int> nums { 1, 2, 1, 2, 6, 7, 5, 1 };
    int k = 2;
    auto res = Solution2().maxSumOfThreeSubarrays(nums, k);
    for (const auto &ele : res) {
        cout << ele << ' ';
    }
    return 0;
}