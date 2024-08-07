#include "D:/distake/Coding/head_file.h"


class Solution {
private:
    vector<int> ans;
    vector<vector<int>> res;
    void dfs(vector<int>& nums, int start) {
        if (start <= nums.size()) {
            res.push_back(ans);
        }
        for (int i = start; i < nums.size(); ++i) {
            ans.push_back(nums[i]);
            dfs(nums, i + 1);
            ans.pop_back();
        }
    }
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        dfs(nums, 0);
        return res;
    }
};


int main() {
    Solution s;
    vector<int> nums {1, 2, 3};
    vector<vector<int>> res = s.subsets(nums);
    for (auto& v : res) {
        for (auto& val : v) {
            cout << val << " ";
        }
        cout << '\n';
    }
    return 0;
}