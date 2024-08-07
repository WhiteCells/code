#include "D:\distake\Coding\head_file.h"

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> retv;
        sort(nums.begin(), nums.end());
        for (int i = 0; i < nums.size(); ++i) {
            // 后面不会再有满足条件的三元组
            if (nums[i] > 0) {
                return retv;
            }
            // i 下标元素的去重
            /* 错误写法
            if (nums[i] == nums[i + 1]) continue;
            // 忽略 -2 -2 4 的情况
            */
            if (i > 1 && nums[i] == nums[i - 1]) continue;

            int left = i + 1;
            int right = nums.size() - 1;
            while (left < right) {
                int sum = nums[i] + nums[left] + nums[right];
                // 小了
                if (sum < 0) left++;
                // 大了
                else if (sum > 0) right--;
                // 是三元组
                else {
                    retv.push_back(vector<int>{nums[i], nums[left], nums[right]});
                    // 数据相同的元素进行去重
                    while (left < right && nums[left] == nums[left + 1]) left++;
                    while (left < right && nums[right] == nums[right - 1]) right--;
                    // 左右指针同时收缩
                    left++;
                    right--;
                }
            }
        }
        return retv;
    }
};

int main() {
    vector<int> v{-1, 0, 1, 2, -1, -4};
    Solution s;
    vector<vector<int>> ret = s.threeSum(v);
    for (auto& v : ret) {
        for (auto& val : v) {
            cout << val << " ";
        }
        cout << endl;
    }
    return 0;
}