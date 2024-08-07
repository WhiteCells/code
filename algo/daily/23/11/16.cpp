#include "../../head_file.h"

/*
problme:

url: https://leetcode.cn/problems/longest-even-odd-subarray-with-threshold/description/
 */

// time complexity: O()
// spatial complexity: O()
class Solution {
public:
    int longestAlternatingSubarray(vector<int> &nums, int threshold) {
        int res = 0, n = nums.size();
        for (int i = 0; i < n; ++i) {
            int cur = 0;
            if (!(nums[i] & 1) && nums[i] <= threshold) {
                cur = 1;
                for (int j = i; j < n - 1; ++j) {
                    if (nums[j] > threshold || nums[j + 1] > threshold || !((nums[j] ^ nums[j + 1]) & 1)) {
                        break;
                    }
                    ++cur;
                }
                res = max(res, cur);
            }
        }
        return res;
    }
};

int main() {
    vector<int> nums { 3, 2, 5, 4 };
    int threshold = 5;
    cout << Solution().longestAlternatingSubarray(nums, threshold) << endl;
    return 0;
}