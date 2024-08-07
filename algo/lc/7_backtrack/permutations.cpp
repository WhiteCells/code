#include "D:/distake/Coding/head_file.h"


class Solution {
private:
    vector<int> ans;
    vector<vector<int>> res;
    void dfs(vector<int>& nums, vector<bool>& used) {
        if (ans.size() == nums.size()) {
            res.push_back(ans);
            return;
        }
        for (int i = 0; i < nums.size(); ++i) {
            if (used[i]) { // 使用过
                continue;
            }
            used[i] = true;
            ans.push_back(nums[i]);
            dfs(nums, used);
            used[i] = false;
            ans.pop_back();
        }
    }
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<bool> used(nums.size(), false);
        dfs(nums, used);
        return res;
    }
};


int main() {
    Solution s;
    vector<int> nums {1, 2, 3};
    vector<vector<int>> res = s.permute(nums);
    for (auto& v : res) {
        for (auto& val : v) {
            cout << val << " ";
        }
        cout << '\n';
    }
    return 0;
}