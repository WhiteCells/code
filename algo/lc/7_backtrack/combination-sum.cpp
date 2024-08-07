#include "D:/distake/Coding/head_file.h"


class Solution {
private:
    vector<int> path;
    vector<vector<int>> result;
    void backtrack(vector<int>& candidates, int target, int sum, int start) {
        if (sum == target) {
            result.push_back(path);
            return;
        }
        if (sum > target) {
            return;
        }
        for (int i = start; i < (int)candidates.size(); ++i) {
            path.push_back(candidates[i]);
            sum += candidates[i];
            backtrack(candidates, target, sum, i);
            sum -= candidates[i];
            path.pop_back();
        }
    }
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        backtrack(candidates, target, 0, 0);
        return result;
    }
};


int main() {
    Solution s;
    vector<int> v { 2, 3, 6, 7 };
    vector<vector<int>> res = s.combinationSum(v, 7);
    return 0;
}