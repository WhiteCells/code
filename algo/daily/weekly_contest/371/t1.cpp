#include "../../head_file.h"

/*
problme:

url:
 */

// time complexity: O()
// spatial complexity: O()
class Solution {
public:
    int maximumStrongPairXor(vector<int> &nums) {
        int res = INT_MIN, n = nums.size();
        for (int i = 0; i < n; ++i) {
            for (int j = i; j < n; ++j) {
                if (abs(nums[i] - nums[j]) <= min(nums[i], nums[j])) {
                    res = max(res, nums[i] ^ nums[j]);
                }
            }
        }
        return res;
    }
};

int main() {
    vector<int> nums { 10, 100 };
    cout << Solution().maximumStrongPairXor(nums) << endl;
    return 0;
}