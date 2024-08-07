#include "D:/distake/Coding/head_file.h"


class Solution {
private:
    vector<string> ans;
    vector<vector<string>> res;
    bool isPalindrome(const string& s, int start, int end) { // 左闭右闭
        for (int i = start, j = end; i < j; ++i, --j) {
            if (s[i] != s[j]) {
                return false;
            }
        }
        return true;
    }
    void dfs(string& s, int start) { // start 也是分割点，也是每一次的起点
        if (start >= s.size()) {
            res.push_back(ans);
            return;
        }
        for (int i = start; i < s.size(); ++i) {
            if (isPalindrome(s, start, i)) { // [start, end]
                string subStr = s.substr(start, i - start + 1); // 记录这个区间内的回文串
                ans.push_back(subStr);
            }
            else {
                // 该区间不是回文串，继续下一个区间，换分割点
                continue;
            }
            dfs(s, i + 1);
            ans.pop_back();
        }
    }
public:
    vector<vector<string>> partition(string s) {
        dfs(s, 0);
        return res;
    }
};


int main() {
    Solution s;
    string str = "abb";
    vector<vector<string>> res = s.partition(str);
    for (auto& v : res) {
        for (auto& val : v) {
            cout << val << " ";
        }
        cout << '\n';
    }
    return 0;
}