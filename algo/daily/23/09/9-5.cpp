#include "../../head_file.h"

/*
problme:

url:
*/

class Solution {
public:
    int minNumber(vector<int> &nums1, vector<int> &nums2) {
        int res = INT_MAX, m = nums1.size(), n = nums2.size();
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (nums1[i] == nums2[j]) {
                    res = min(res, nums1[i]);
                }
                else {
                    res = min(res, min(nums1[i], nums2[j]) * 10 + max(nums1[i], nums2[j]));
                }
            }
        }
        return res;
    }
};

class Solution2 {
public:
    int minNumber(vector<int> &nums1, vector<int> &nums2) {
        int mn = INT_MAX, a = INT_MAX, b = INT_MAX, mp[10] = { 0 };
        for (const auto &x : nums1) {
            mp[x] = 1;
            a = min(a, x);
        }
        for (const auto &x : nums2) {
            if (mp[x]) { // 存在相等的值
                mn = min(mn, x);
            }
            b = min(b, x);
        }
        if (INT_MAX != mn) {
            return mn;
        }
        return min(a, b) * 10 + max(a, b);
    }
};

int main() {
    vector<int> nums1 { 4, 1, 3 }, nums2 { 5, 7 };
    cout << Solution().minNumber(nums1, nums2) << '\n';
    cout << Solution2().minNumber(nums1, nums2) << '\n';
    return 0;
}