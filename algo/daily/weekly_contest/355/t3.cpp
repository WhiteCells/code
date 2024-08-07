#include "../../head_file.h"

/*
 * @Author: Eorys
 * @Date: 2023-07-23 09:13:47
 * @Last Modified by: Eorys
 * @Last Modified time: 2023-07-23 09:13:47
 * @Description: https://leetcode.cn/problems/maximum-number-of-groups-with-increasing-length/
*/

class Solution {
public:
    int maxIncreasingGroups(vector<int>& usageLimits) {
        sort(usageLimits.begin(), usageLimits.end());
        int ans = 0;
        long long left = 0;
        for (const auto& usage_cnt : usageLimits) {
            left += usage_cnt;
            if (left >= ans + 1) {
                left -= ans + 1;
                ans++;
            }
        }
        return ans;
    }
};


int main() {
    Solution s;
    // auto usageLimits = vector<int>{ 1, 2, 5 };
    auto usageLimits = vector<int>{ 2, 1, 2 };
    // auto usageLimits = vector<int>{ 1, 1 };
    cout << s.maxIncreasingGroups(usageLimits);
    return 0;
}