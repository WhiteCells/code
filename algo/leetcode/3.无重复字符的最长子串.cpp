/*
 * @lc app=leetcode.cn id=3 lang=cpp
 *
 * [3] 无重复字符的最长子串
 *
 * https://leetcode.cn/problems/longest-substring-without-repeating-characters/description/
 *
 * algorithms
 * Medium (39.17%)
 * Likes:    9503
 * Dislikes: 0
 * Total Accepted:    2.4M
 * Total Submissions: 6.3M
 * Testcase Example:  '"abcabcbb"'
 *
 * 给定一个字符串 s ，请你找出其中不含有重复字符的 最长子串 的长度。
 *
 *
 *
 * 示例 1:
 *
 *
 * 输入: s = "abcabcbb"
 * 输出: 3
 * 解释: 因为无重复字符的最长子串是 "abc"，所以其长度为 3。
 *
 *
 * 示例 2:
 *
 *
 * 输入: s = "bbbbb"
 * 输出: 1
 * 解释: 因为无重复字符的最长子串是 "b"，所以其长度为 1。
 *
 *
 * 示例 3:
 *
 *
 * 输入: s = "pwwkew"
 * 输出: 3
 * 解释: 因为无重复字符的最长子串是 "wke"，所以其长度为 3。
 * 请注意，你的答案必须是 子串 的长度，"pwke" 是一个子序列，不是子串。
 *
 *
 *
 *
 * 提示：
 *
 *
 * 0 <= s.length <= 5 * 10^4
 * s 由英文字母、数字、符号和空格组成
 *
 *
 */
#include "../head_file.h"
// @lc code=start
class Solution {
public:
    // 5% hhh
    // int lengthOfLongestSubstring(string s) {
    //     string cur;
    //     unordered_map<char, int> m; // val : index
    //     int n = s.size(), res_len = 0;
    //     for (int i = 0; i < n; ++i) {
    //         if (m.find(s[i]) != m.end()) {
    //             i = m[s[i]];
    //             cur.clear();
    //             m.clear();
    //         }
    //         else {
    //             cur += s[i];
    //             res_len = max(res_len, (int)cur.size());
    //             m[s[i]] = i;
    //         }
    //     }
    //     return res_len;
    // }
    int lengthOfLongestSubstring(string s) {
        string cur;
        vector<int> dict(256, -1); // val : index
        int max_len = 0, start = -1, n = s.size();
        for (int i = 0; i < n; ++i) {
            if (dict[s[i]] > start) { // s[i] 之前出现过
                start = dict[s[i]];
            }
            dict[s[i]] = i;
            max_len = max(max_len, i - start);
        }
        return max_len;
    }
};
// @lc code=end

int main(int argc, char const *argv[]) {
    // string str = "abcabcbb";
    string str = "pwwkew";
    // string str = "dvdf";
    Solution s;
    cout << s.lengthOfLongestSubstring(str) << '\n';
    return 0;
}
