#include "../../head_file.h"

/*
problme:

url:
 */

class Solution {
public:
    int minimumSum(vector<int> &nums) {
        int n = nums.size();
        vector<int> pre(n), suf(n);
        pre[0] = nums[0];
        suf[n - 1] = nums[n - 1];
        // 0 -> n - 2
        for (int i = 1; i < n; ++i) {
            pre[i] = min(nums[i], pre[i - 1]);
        }
        // n - 2 -> 1
        for (int i = n - 2; i >= 0; --i) {
            suf[i] = min(nums[i], suf[i + 1]);
        }
        int res = INT_MAX;
        for (int i = 1; i + 1 < n; ++i) {
            if (nums[i] > pre[i - 1] && nums[i] > suf[i + 1]) {
                res = min(res, pre[i - 1] + nums[i] + suf[i + 1]);
            }
        }
        return res == INT_MAX ? -1 : res;
    }
};

int main() {
    vector<int> nums {8, 6, 1, 5, 3};
    std::cout << Solution().minimumSum(nums) << std::endl;
    return 0;
}