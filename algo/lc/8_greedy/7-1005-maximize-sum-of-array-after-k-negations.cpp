#include "D:/distake/Coding/head_file.h"

/*
 * @Author: WhiteCells
 * @Date: 2023-05-21 14:30:42
 * @Last Modified by: WhiteCells
 * @Last Modified time: 2023-05-21 14:30:42
 * @Description: 1005.K 次取反后最大化的数组和
 * https://leetcode.cn/problems/maximize-sum-of-array-after-k-negations/
*/

class Solution {
public:
    int largestSumAfterKNegations(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end()); // 排序后每次对小的值进行取反操作
        int cnt = 0; // 取反次数，cnt < k
        int sum = 0; // 和
        int absMin = 101;
        for (int i = 0; i < nums.size(); ++i) {
            if (absMin > abs(nums[i])) { // 找这个数组中绝对值最小的数
                absMin = abs(nums[i]);
            }
            if (nums[i] < 0 && cnt < k) { // 尽可能先将负数变成正数，同时取反次数要小于 k
                nums[i] *= -1;
                ++cnt;
            }
            if (nums[i] == 0 && (k - cnt) % 2 && cnt < k) { // 取反次数剩余奇数次，0需要取反，将取反次数变为偶数
                ++cnt;
            }
            sum += nums[i];
        }
        if ((k - cnt) % 2) { // 剩下的取反次数为奇数时，绝对值最小的那个数改为负数，保证和最大
            sum -= 2 * absMin;
        }
        return sum;
    }
};


int main() {
    vector<int> nums {-1, 0, 2, 3};
    Solution s;
    cout << s.largestSumAfterKNegations(nums, 3);
    return 0;
}