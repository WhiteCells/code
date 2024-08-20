#include "../../head_file.h"

/*
problme: 

url: https://leetcode.cn/problems/special-array-ii/
 */

class Solution {
public:
    vector<bool> isArraySpecial(vector<int>& nums, vector<vector<int>>& queries) {
        vector<int> prev(nums.size(), 0);
        for (int i = 1; i < nums.size(); ++i) {
            prev[i] = (nums[i] ^ nums[i - 1]) & 1;
        }
        for (int i = 1; i < prev.size(); ++i) {
            prev[i] = prev[i - 1] + prev[i];
        }
        vector<bool> res(queries.size());
        for (int i = 0; i < queries.size(); ++i) {
            int begin = queries[i][0], end = queries[i][1];
            res[i] = end - begin == prev[end] - prev[begin];
        }
        return res;
    }
};

int main() {
    vector<int> nums {4, 3, 1, 6};
    vector<vector<int>> queries {{2, 3}};
    auto res = Solution().isArraySpecial(nums, queries);
    return 0;
}