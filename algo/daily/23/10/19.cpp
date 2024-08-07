#include "../../head_file.h"

/*
problme:

url:
 */

// time complexity: O()
// spatial complexity: O()
class Solution {
public:
    int tupleSameProduct(vector<int> &nums) {
        int n = nums.size();
        unordered_map<int, int> mp;
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                ++mp[nums[i] * nums[j]];
            }
        }
        int res = 0;
        for (const auto &ele : mp) {
            res += ele.second * (ele.second - 1) * 4;
        }
        return res;
    }
};

int main() {
    
    return 0;
}