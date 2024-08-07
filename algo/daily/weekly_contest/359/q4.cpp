#include "../../head_file.h"

/*
problme:

url:
@Author: Eorys
@Date: 2023-08-20 11:36:36
@Last Modified by: Eorys
@Last Modified time: 2023-08-20 11:36:36
@Description:
*/

class Solution {
public:
    int longestEqualSubarray(vector<int>& nums, int k) {
        int res = 0;
        for (int i = 0; i < nums.size(); ++i) {
            int cur = 0;
            int cnt = 0; // number of deletions
            for (int j = i + 1; j < nums.size(); ++j) {
                if (nums[j] == nums[i] && cnt < k) {
                    cur++;
                    res = max(res, cur);
                }
                else if (nums[j] != nums[i]) {
                    cnt++;
                    continue;
                }
                else if (cnt >= k) {
                    break;
                }
            }
        }
        return res;
    }
};


int main() {
    vector<int> nums { 1, 3, 2, 3, 1, 3 };
    int k = 3;
    Solution s;
    cout << s.longestEqualSubarray(nums, k) << '\n';
    return 0;
}