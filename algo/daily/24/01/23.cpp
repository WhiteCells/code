#include "../../head_file.h"

/*
problme: 

url: https://leetcode.cn/problems/longest-alternating-subarray/description/
 */

class Solution {
public:
    int alternatingSubarray(vector<int>& nums) {
        int res = -1;
        for (int i = 0; i < nums.size(); ++i) {
            int flag = 1;
            for (int j = i + 1; j < nums.size(); ++j) {
                if (flag == nums[j] - nums[j - 1]) {
                    res = max(res, j - i + 1);
                    flag *= -1; 
                } else {
                    break;
                }
            }
        }
        return res;
    }
};

int main() {
    vector<int> nums {2, 3, 4, 3, 4};
    cout << Solution().alternatingSubarray(nums) << endl;
    return 0;
}