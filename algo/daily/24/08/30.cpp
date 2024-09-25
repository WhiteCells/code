#include "../../head_file.h"

/*
problme:

url: https://leetcode.cn/problems/sum-of-digit-differences-of-all-pairs/description/
 */

class Solution
{
public:
    long long sumDigitDifferences(vector<int> &nums)
    {
        // 4 5 3
        // 45 43 53
        long long res = 0;
        int n = nums.size();
        while (nums[0] > 0) {
            vector<int> cnt(10);
            for (int i = 0; i < n; i++) {
                cnt[nums[i] % 10]++;
                nums[i] /= 10;
            }
            for (int i = 0; i < 10; i++) {
                res += (long long)(n - cnt[i]) * cnt[i];
            }
        }
        return res / 2;
    }
};

int main()
{

    return 0;
}