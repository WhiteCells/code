#include "D:\distake\Coding\head_file.h"

class Solution {
public:
    void SwapChar(string& s, int start, int end) {
        // 结束条件是 i < j，不是 i < s.size() / 2 或者 j > s.size() / 2
        for (int i = start, j = end; i < j; ++i, --j) {
            s[i] ^= s[j];
            s[j] ^= s[i];
            s[i] ^= s[j];
        }
    }
    string reverseStr(string s, int k) {
        // 每次向后走 2k
        for (int i = 0; i < s.size(); i += 2 * k) {
            // 如果剩余字符小于 2k 但大于或等于 k 个，则反转前 k 个字符，其余字符保持原样。
            if (i + k <= s.size()) SwapChar(s, i, i + k - 1);
            // 如果剩余字符少于 k 个，则将剩余字符全部反转。
            else SwapChar(s, i, s.size() - 1);
        }
        return s;
    }
};

int main() {
    Solution s;
    string s1 = "abcd";
    cout << s.reverseStr(s1, 4);
    return 0;
}