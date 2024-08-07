#include "../../head_file.h"

/*
problme: 

url: https://leetcode.cn/problems/collecting-chocolates/description
 */

// TODO
class Solution {
public:
    long long minCost(vector<int>& nums, int x) {
        int n = nums.size();
        vector<int> f(nums);
        long long res = accumulate(f.begin(), f.end(), 0LL);
        for (int i = 1; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                f[j] = min(f[j], nums[(i + j) % n]);
            }
            res = min(res, (long long)i * x + accumulate(f.begin(), f.end(), 0LL));
        }
        return res;
    }
};

int main() {
    
    return 0;
}