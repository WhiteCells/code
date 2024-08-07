#include "../../head_file.h"

/*
problme: 

url: https://leetcode.cn/problems/sum-of-values-at-indices-with-k-set-bits/
 */

class Solution {
public:
    int sumIndicesWithKSetBits(vector<int>& nums, int k) {
        int res = 0;
        for (int i = 0; i < nums.size(); ++i) {
            int cnt = 0, tmp = i;
            while (tmp) {
                cnt += tmp & 1;
                tmp >>= 1;
            }
            res += cnt == k ? nums[i] : 0;
        }
        return res;
    }
};

int main() {
    vector<int> nums {5, 10, 1, 5, 2};
    int k = 1;
    cout << Solution().sumIndicesWithKSetBits(nums, k) << endl;
    return 0;
}