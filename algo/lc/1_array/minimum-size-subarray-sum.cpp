#include "../../head_file.h"

class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int return_length = INT32_MAX;
        int i = 0; // 滑动窗口起始位置
        int sum = 0; // 滑动窗口数值和
        int sub_length = 0; // 滑动窗口长度
        for (int j = 0; j < nums.size(); j++) {
            // 滑动窗口数值和
            sum += nums[j];
            // 对 sum 和 target 进行判断
            while (sum >= target) {
                // 修改滑动窗口长度
                sub_length = j - i + 1;
                return_length = return_length < sub_length ? return_length : sub_length;
                sum -= nums[i];
                ++i;
            }
        }
        return return_length == INT32_MAX ? 0 : return_length;
    }
};

int main() {
    Solution s;
    vector<int> v {2, 3, 1, 2, 4, 3};
    cout << s.minSubArrayLen(7, v);
    return 0;
}