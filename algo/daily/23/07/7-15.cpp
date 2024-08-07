#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        if (nums.size() < 4) {
            return {};
        }
        sort(nums.begin(), nums.end());
        if (nums[0] > 0 && nums[0] > target) {
            return {};
        }
        vector<vector<int>> ans;
        for (int i = 0; i < nums.size(); ++i) {
            if (nums[i] > 0 && nums[i] > target) {
                break;
            }
            if (i > 0 && nums[i] == nums[i - 1]) {
                continue;
            }
            for (int j = i + 1; j < nums.size(); ++j) {
                long long two_sum = nums[i] + nums[j];
                if (two_sum > 0 && two_sum > target) {
                    break;
                }
                if (j > i + 1 && nums[j] == nums[j - 1]) {
                    continue;
                }
                int left = j + 1;
                int right = nums.size() - 1;
                while (left < right) {
                    long long other_sum = nums[left] + nums[right];
                    if (two_sum + other_sum > target) {
                        --right;
                    }
                    else if (two_sum + other_sum < target) {
                        ++left;
                    }
                    else {
                        ans.push_back({ nums[i], nums[j], nums[left], nums[right] });
                        while (left < right && nums[left] == nums[left + 1]) {
                            ++left;
                        }
                        while (left < right && nums[right] == nums[right - 1]) {
                            --right;
                        }
                        ++left;
                        --right;
                    }
                }
            }
        }
        return ans;
    }
};

int main() {
    // vector<int> nums{ 1, 0, -1, 0, -2, 2 };
    // int target = 0;
    vector<int> nums{ 0, 0, 0, 1000000000, 1000000000, 1000000000, 1000000000 };
    int target = 1000000000;
    Solution s;
    vector<vector<int>> res = s.fourSum(nums, target);
    for (auto& ele : res) {
        for (auto& val : ele) {
            cout << val << " ";
        }
        cout << '\n';
    }
    return 0;
}