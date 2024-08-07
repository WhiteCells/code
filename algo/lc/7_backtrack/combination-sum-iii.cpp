#include <iostream>
#include <vector>

using namespace std;

class Solution {
private:
    vector<vector<int>> result;
    vector<int> path;
    int pathSum(vector<int>& path) {
        int sum = 0;
        for (int i = 0; i < (int)path.size(); ++i) {
            sum += path[i];
        }
        return sum;
    }
    void backtrack(int start, int k, int n) {
        if (path.size() == k && pathSum(path) == n) {
            result.push_back(path);
            return;
        }
        if (pathSum(path) > n) {
            return;
        }
        for (int i = start; i < 10; ++i) {
            path.push_back(i);
            backtrack(i + 1, k, n);
            path.pop_back();
        }
    }
public:
    vector<vector<int>> combinationSum3(int k, int n) {
        if (k > n) {
            return {};
        }
        backtrack(1, k, n);
        return result;
    }
};

int main() {
    Solution s;
    vector<vector<int>> res = s.combinationSum3(2, 9);
    for (const auto& v : res) {
        for (const auto& val : v) {
            cout << val << " ";
        }
        cout << '\n';
    }
    return 0;
}