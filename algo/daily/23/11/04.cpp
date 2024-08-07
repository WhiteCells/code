#include "../../head_file.h"

/*
problme:

url:
 */

// time complexity: O()
// spatial complexity: O()
class Solution {
public:
    int findMaximumXOR(vector<int> &nums) {
        int it = *max_element(nums.begin(), nums.end());
        // 0 <= nums[i] <= 2^31 - 1
        int mx_bit = 31;
        for (; mx_bit >= 0; --mx_bit) {
            if ((1 << mx_bit) & it) {
                break;
            }
        }
        int res = 0, delete_bit = 0, n = nums.size();
        unordered_set<int> s;
        for (int i = mx_bit; i >= 0; --i) {
            s.clear();
            delete_bit |= (1 << i); // 1000 -> 1100 -> 1110 -> 1111
            int now = res | (1 << i);
            for (auto num : nums) {
                num &= delete_bit; // 低于 i 位变为 0
                if (s.count(now ^ num)) {
                    res = now;
                    break;
                }
                s.insert(num);
            }
        }
        return res;
    }
};

#include <utility>

int main() {
    vector<int> nums { 3, 10, 5, 25, 2, 8 };
    cout << Solution().findMaximumXOR(nums) << endl;
    return 0;
}