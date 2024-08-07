#include "../../head_file.h"

/*
problme:

url:
 */

// time complexity: O()
// spatial complexity: O()
class Solution {
public:
    vector<int> maximumSumQueries(vector<int> &nums1, vector<int> &nums2, vector<vector<int>> &queries) {

    }
};
int main() {
    vector<int> nums1 { 4, 3, 1, 2 };
    vector<int> nums2 { 2, 4, 9, 5 };
    vector<vector<int>> queries {
        { 4, 1 },
        { 1, 3 },
        { 2, 5 }
    };
    auto res = Solution().maximumSumQueries(nums1, nums2, queries);
    for (const auto &ele : res) {
        cout << ele << ' ';
    }
    return 0;
}