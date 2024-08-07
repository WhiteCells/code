#include <iostream>
#include <string>

using namespace std;
// https://leetcode.cn/problems/reverse-string/

class Solution {
public:
    void reverseString(string& s) {
        int s_len = s.size();
        // for (int i = 0; i < s_len / 2; ++i) {
        //     auto tmp = s[i];
        //     s[i] = s[s_len - 1 - i];
        //     s[s_len - 1 - i] = tmp;
        // }
        for (int i = 0, j = s_len - 1; i < j; ++i, --j) {
            // auto tmp = s[j];
            // s[j] = s[i];
            // s[i] = tmp;
            s[j] ^= s[i];
            s[i] ^= s[j];
            s[j] ^= s[i];
        }
    }
};

int main() {
    string str = "hello";
    Solution s;
    s.reverseString(str);
    cout << str << '\n';
    return 0;
}