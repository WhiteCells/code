#include "../../head_file.h"

/*
problme: 

url: https://leetcode.cn/problems/minimum-string-length-after-removing-substrings/
 */

class Solution {
public:
    int minLength(string s) {
        stack<char> st;
        for (int i = 0; i < s.size(); ++i) {
            if (st.empty()) {
                st.push(s[i]);
            } else if (('A' == st.top() && 'B' == s[i]) || ('C' == st.top() && 'D' == s[i])) {
                st.pop();
            } else {
                st.push(s[i]);
            }
        }
        return st.size();
    }
};

int main() {
    string s = "CCCCDDDD";
    cout << Solution().minLength(s) << std::endl;
    return 0;
}