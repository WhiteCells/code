#include "../../head_file.h"

/*
problme:

url:
 */

// time complexity: O()
// spatial complexity: O()
class Solution {
public:
    long long minSum(vector<int> &nums1, vector<int> &nums2) {
        long long sum1 = 0, sum2 = 0;
        int cnt1 = 0;
        for (const auto &num : nums1) {
            sum1 += num;
            if (0 == num) {
                ++cnt1;
            }
        }
        int cnt2 = 0;
        for (const auto &num : nums2) {
            sum2 += num;
            if (0 == num) {
                ++cnt2;
            }
        }
        long long res = 0;
        sum1 += cnt1; // 所有 0 变为 1 尽可能使总和小
        sum2 += cnt2;
    // 优先考略值
        if (sum1 > sum2) {
            return sum1;
        } else if (sum1 < sum2) {
            return sum2;
        } else {
            return sum1;
        }
        return -1;
    }
};

int main() {
    // vector<int> nums1 { 3, 2, 0, 1, 0 };
    // vector<int> nums2 { 6, 5, 0 };
    // vector<int> nums1 { 0, 7, 28, 17, 18 };
    // vector<int> nums2 { 1, 2, 6, 26, 1, 0, 27, 3, 0, 30 };
    vector<int> nums1 { 2, 0, 2, 0 };
    vector<int> nums2 { 1, 4 };
    cout << Solution().minSum(nums1, nums2) << endl;
    return 0;
}