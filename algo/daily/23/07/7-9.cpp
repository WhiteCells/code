#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;


class Solution {
private:
    vector<int> path;
    vector<vector<int>> res;
    void dfs(vector<int>& nums, int sum, int cnt, int start, vector<bool>& used) {
        if (0 == sum && 3 == cnt) {
            res.push_back(path);
            return;
        }
        if (0 != sum && 3 < cnt) {
            return;
        }
        for (int i = start; i < nums.size(); ++i) {
            if (used[i]) {
                continue;
            }
            path.push_back(nums[i]);
            used[i] = true;
            sum += nums[i];
            cnt++;
            dfs(nums, sum, cnt, start + 1, used);
            path.pop_back();
            used[i] = false;
            sum -= nums[i];
            cnt--;
        }
    }
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<bool> used(nums.size(), false);
        dfs(nums, 0, 0, 0, used);
        return res;
    }
};


// 排序 + 双指针
class Solution3 {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        int n = nums.size();
        if (n < 3) {
            return {};
        }
        sort(nums.begin(), nums.end()); // 排序
        if (nums[0] > 0) { // 第一个数是最小的值，> 0 就不会产生和为 0 的三个数
            return {};
        }
        vector<vector<int>> ans;
        for (int i = 0; i <= n - 3; ++i) {
            if (i != 0 && nums[i] == nums[i - 1]) { // 去重
                continue;
            }
            int left = i + 1, right = n - 1, target = -nums[i];
            while (left < right) {
                if (left > i + 1 && nums[left] == nums[left - 1]) { // 去重
                    ++left; // 左区间收缩
                    continue;
                }
                if (nums[left] + nums[right] == target) {
                    ans.push_back({ nums[left], nums[right], nums[i] });
                    ++left;
                    --right;
                }
                else if (nums[left] + nums[right] < target) {
                    ++left;
                }
                else {
                    --right;
                }
            }
        }
        return ans;
    }
};


int main() {
    Solution3 s;
    vector<int>nums{ -1, 0, 1, 2, -1, -4 };
    vector<vector<int>> res = s.threeSum(nums);

    for (const auto& ele : res) {
        for (const auto& val : ele) {
            cout << val << " ";
        }
        cout << '\n';
    }
    return 0;
}