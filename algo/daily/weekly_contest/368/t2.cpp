#include "../../head_file.h"

/*
problme: 

url: 
 */

// time complexity: O()
// spatial complexity: O()
class Solution1 {
public:
    int minimumSum(vector<int>& nums) {
        int n = nums.size();
        // f[i] 表示前 i 个(包括 i)元素中的最小值
        // 从左至右维护最小值数组 f[i]
        int pre[n];
        pre[0] = nums[0];
        for (int i = 1; i < n; ++i) { // 1 -> n - 1
            pre[i] = min(pre[i - 1], nums[i]);
        }
        // g[i] 表示后 i 个(包括 i)元素中的最小值
        // 从右至左维护最小值数组 g[i]
        int suf[n];
        pre[n - 1] = nums[n - 1];
        for (int i = n - 2; i >= 0; --i) { // 0 <- n - 2
            suf[i] = min(suf[i + 1], nums[i]);
        }

        int res = INT_MAX;
        // 枚举 j
        for (int j = 1; j < n - 1; ++j) { // 1 -> n - 2
            if (nums[j] > pre[j - 1] && nums[j] > suf[j + 1]) {
                res = min(res, nums[j] + pre[j - 1] + suf[j + 1]);
            }
        }
        return INT_MAX == res ? -1 : res;
    }
};

class Solution2 {
public:
    int minimumSum(vector<int>& nums) {
        int n = nums.size();
        int pre = nums[0];
        int suf[n];
        suf[n - 1] = nums[n - 1];
        for (int i = n - 2; i >= 0; --i) { // 0 <- (n - 2)
            suf[i] = min(suf[i + 1], nums[i]);
        }
        int res = INT_MAX;
        // 枚举 j
        for (int j = 1; j < n - 1; ++j) { // 1 -> n - 2
            if (nums[j] > pre && nums[j] > suf[j + 1]) {
                res = min(res, nums[j] + pre + suf[j + 1]);
            }
            pre = min(pre, nums[j - 1]);
        }
        return INT_MAX == res ? -1 : res;
    }
};

int main() {
    
    return 0;
}