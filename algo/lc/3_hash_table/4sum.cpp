#include "D:\distake\Coding\head_file.h"

class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        if (nums.size() < 4) return {};
        vector<vector<int>> retv;
        sort(nums.begin(), nums.end());
        for (int i = 0; i < nums.size(); ++i) {
            // 剪枝处理
            if (nums[i] >= 0 && nums[i] > target) break;
            // 去重
            if (i > 0 && nums[i] == nums[i - 1]) continue;
            for (int j = i + 1; j < nums.size(); ++j) {
                // 剪枝处理
                if (nums[i] + nums[j] >= 0 && nums[i] + nums[j] > target) break;
                // 去重
                if (j > i + 1 && nums[j] == nums[j - 1]) continue;

                int k = j + 1;
                int m = nums.size() - 1;

                while (k < m) {
                    if ((long)nums[i] + nums[j] + nums[k] + nums[m] > target) m--;
                    else if ((long)nums[i] + nums[j] + nums[k] + nums[m] < target)  k++;
                    else {
                        retv.push_back(vector<int>{nums[i], nums[j], nums[k], nums[m]});
                        while (k < m && nums[k] == nums[k + 1]) k++;
                        while (k < m && nums[m] == nums[m - 1]) m--;
                        k++;
                        m--;
                    }
                }
            }
        }
        return retv;
    }
};

class Solution1 {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        vector<vector<int>> result;
        sort(nums.begin(), nums.end());
        for (int k = 0; k < nums.size(); k++) {
            // 剪枝处理
            if (nums[k] > target && nums[k] >= 0) {
                break; // 这里使用break，统一通过最后的return返回
            }
            // 对nums[k]去重
            if (k > 0 && nums[k] == nums[k - 1]) {
                continue;
            }
            for (int i = k + 1; i < nums.size(); i++) {
                // 2级剪枝处理
                if (nums[k] + nums[i] > target && nums[k] + nums[i] >= 0) {
                    break;
                }

                // 对nums[i]去重
                if (i > k + 1 && nums[i] == nums[i - 1]) {
                    continue;
                }
                int left = i + 1;
                int right = nums.size() - 1;
                while (right > left) {

                    // nums[k] + nums[i] + nums[left] + nums[right] > target 会溢出
                    if (long(nums[k] + nums[i] + nums[left] + nums[right] > target)) {
                        right--;
                        // nums[k] + nums[i] + nums[left] + nums[right] < target 会溢出
                    }
                    else if ((long)nums[k] + nums[i] + nums[left] + nums[right] < target) {
                        left++;
                    }
                    else {
                        result.push_back(vector<int>{nums[k], nums[i], nums[left], nums[right]});
                        // 对nums[left]和nums[right]去重
                        while (right > left && nums[right] == nums[right - 1]) right--;
                        while (right > left && nums[left] == nums[left + 1]) left++;

                        // 找到答案时，双指针同时收缩
                        right--;
                        left++;
                    }
                }

            }
        }
        return result;
    }
};

int main() {
    vector<int> v{2, 2, 2, 2, 2};
    Solution s;
    vector<vector<int>> ret = s.fourSum(v, 0);
    for (auto& v : ret) {
        for (auto& val : v) {
            cout << val << " ";
        }
        cout << endl;
    }
    return 0;
}