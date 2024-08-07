#include "../../head_file.h"

/*

 */

// time complexity: O()
// spatial complexity: O()
class Solution {
public:
    vector<int> findIndices(vector<int> &nums, int indexDifference, int valueDifference) {
        int n = nums.size();
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (abs(i - j) >= indexDifference && abs(nums[i] - nums[j]) >= valueDifference) {
                    return { i, j };
                }
            }
        }
        return { -1, -1 };
    }
};

int main() {

    return 0;
}