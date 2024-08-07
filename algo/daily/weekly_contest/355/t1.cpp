#include "../../head_file.h"

/*
 * @Author: Eorys
 * @Date: 2023-07-23 09:13:36
 * @Last Modified by: Eorys
 * @Last Modified time: 2023-07-23 09:13:36
 * @Description: https://leetcode.cn/problems/split-strings-by-separator/
*/

class Solution {
public:
    vector<string> splitWordsBySeparator(vector<string>& words, char separator) {
        vector<string> ans;
        for (const auto& str : words) {
            string s1;
            string s2;
            for (const auto& c : str) {
                if (c == separator && !s1.empty()) {
                    ans.push_back(s1);
                    s1 = "";
                    s2 = "";
                }
                else if (c != separator) {
                    s1 += c;
                    s2 += c;
                }
            }
            if (!s2.empty()) {
                ans.push_back(s2);
            }
        }
        return ans;
    }
};


int main() {
    Solution s;
    auto v = vector<string>{ "one.two.three", "four.five", "six" };
    auto sp = '.';
    auto ans = s.splitWordsBySeparator(v, sp);
    for (auto& v : ans) {
        for (auto& val : v) {
            cout << val;
        }
        cout << '\n';
    }
    return 0;
}