#include "D:/distake/Coding/head_file.h"

class Solution {
private:
    vector<int> ans;
    vector<vector<int>> res;
    void dfs(vector<int>& nums, vector<bool>& used) {
        if (ans.size() == nums.size()) { // 收集叶子结点
            res.push_back(ans);
            return;
        }
        for (int i = 0; i < nums.size(); ++i) {
            if (i > 0 && nums[i - 1] == nums[i] && !used[i - 1]) {
                continue;
            }
            if (!used[i]) {
                used[i] = true;
                ans.push_back(nums[i]);
                dfs(nums, used);
                ans.pop_back();
                used[i] = false;
            }
        }
    }
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<bool> used(nums.size(), false);
        dfs(nums, used);
        return res;
    }
};


int main() {
    Solution s;
    vector<int> nums {1, 1, 2};
    vector<vector<int>> res = s.permuteUnique(nums);
    for (auto& v : res) {
        for (auto& val : v) {
            cout << val << " ";
        }
        cout << '\n';
    }
    return 0;
}