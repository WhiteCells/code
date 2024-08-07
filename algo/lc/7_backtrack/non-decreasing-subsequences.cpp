#include "D:/distake/Coding/head_file.h"

class Solution {
private:
    vector<int> ans;
    vector<vector<int>> res;
    void dfs(vector<int>& nums, int start) {
        if (ans.size() > 1) {
            res.push_back(ans);
        }
        unordered_set<int> uset; // 去重
        for (int i = start; i < nums.size(); ++i) {
            if (!ans.empty() && nums[i] < ans.back() || uset.find(nums[i]) != uset.end()) {
                continue;
            }
            uset.insert(nums[i]);
            ans.push_back(nums[i]);
            dfs(nums, i + 1);
            ans.pop_back();
        }
    }
public:
    vector<vector<int>> findSubsequences(vector<int>& nums) {
        dfs(nums, 0);
        return res;
    }
};


int main() {
    Solution s;
    vector<int> nums {1, 2, 2};
    vector<vector<int>> res = s.findSubsequences(nums);
    for (auto& v : res) {
        for (auto& val : v) {
            cout << val << " ";
        }
        cout << '\n';
    }
    return 0;
}