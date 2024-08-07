#include "../../head_file.h"

// 开方数组排序
class Solution {
public:
    vector<int> sortedSquares(vector<int>& nums) {
        int left = 0;
        int right = nums.size() - 1;
        int index = nums.size() - 1; // 从大往小放
        vector<int> ret_v(nums.size());
        for (int i = 0; i < nums.size(); ++i) {
            if (nums[left] * nums[left] > nums[right] * nums[right]) {
                ret_v[index--] = nums[left] * nums[left]; // 放大的
                left++; // 更新左边的下标
            }
            else {
                ret_v[index--] = nums[right] * nums[right];
                right--; // 更新右边的下标
            }
        }
        return ret_v;
    }
};

int main() {
    Solution s;
    vector<int> v { -2, -1, 0, 1, 5 };
    vector<int> ret_v = s.sortedSquares(v);
    for (auto val : ret_v) {
        cout << val << " ";
    }
    return 0;
}