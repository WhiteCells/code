#include "../head_file.h"
/*
 * @lc app=leetcode.cn id=5 lang=cpp
 *
 * [5] 最长回文子串
 *
 * https://leetcode.cn/problems/longest-palindromic-substring/description/
 *
 * algorithms
 * Medium (37.70%)
 * Likes:    6720
 * Dislikes: 0
 * Total Accepted:    1.5M
 * Total Submissions: 3.9M
 * Testcase Example:  '"babad"'
 *
 * 给你一个字符串 s，找到 s 中最长的回文子串。
 *
 * 如果字符串的反序与原始字符串相同，则该字符串称为回文字符串。
 *
 *
 *
 * 示例 1：
 *
 *
 * 输入：s = "babad"
 * 输出："bab"
 * 解释："aba" 同样是符合题意的答案。
 *
 *
 * 示例 2：
 *
 *
 * 输入：s = "cbbd"
 * 输出："bb"
 *
 *
 *
 *
 * 提示：
 *
 *
 * 1 <= s.length <= 1000
 * s 仅由数字和英文字母组成
 *
 *
 */

// @lc code=start
class Solution {
public:
    string longestPalindrome(string s) {
        string res;
        res.push_back(s[0]);
        for (int i = 0; i + 1 < s.size(); ++i) {
            string sub;
            sub.push_back(s[i]);
            for (int j = i + 1; j < s.size(); ++j) {
                // string sub = string(s.begin() + i, s.begin() + j + 1);
                sub.push_back(s[j]);
                if (sub.size() > res.size() && isPalindrome(sub)) {
                    res = sub;
                }
            }
        }
        return res;
    }

private:
    bool isPalindrome(const string &sub) {
        for (int i = 0, j = sub.size() - 1; i < j; ++i, --j) {
            if (sub[i] != sub[j]) {
                return false;
            }
        }
        return true;
    }
};
// @lc code=end


int main() {
    string s = "babad";
    // string s = "cbbd";
    cout << Solution().longestPalindrome(s) << '\n';
    return 0;
}