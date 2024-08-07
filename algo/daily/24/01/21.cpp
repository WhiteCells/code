#include "../../head_file.h"

/*
problme: 

url: https://leetcode.cn/problems/split-array-largest-sum
 */

class Solution {
public:
    int splitArray(vector<int>& nums, int k) {
        long long left = 0, right = 0;
        for (const int num : nums) {
            right += num;
            if (left < num) {
                left = num;
            }
        }
        while (left < right) {
            long long mid = ((right - left) >> 1) + left;
            if (check(nums, mid, k)) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        return left;
    }
private:
    bool check(vector<int> &nums, long long mid, int k) {
        long long sum = 0;
        int cnt = 1;
        for (int i = 0; i < nums.size(); ++i) {
            if (sum + nums[i] > mid) {
                ++cnt;
                sum = nums[i];
            } else {
                sum += nums[i];
            }
        }
        return cnt <= k;
    }
};

int main() {
    vector<int> nums {7, 2, 5, 10, 8};
    int k = 2;
    cout << Solution().splitArray(nums, k) << endl;
    return 0;
}