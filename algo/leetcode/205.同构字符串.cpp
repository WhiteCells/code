#include "../head_file.h"
/*
 * @lc app=leetcode.cn id=205 lang=cpp
 *
 * [205] 同构字符串
 *
 * https://leetcode.cn/problems/isomorphic-strings/description/
 *
 * algorithms
 * Easy (49.08%)
 * Likes:    680
 * Dislikes: 0
 * Total Accepted:    234.8K
 * Total Submissions: 478.2K
 * Testcase Example:  '"egg"\n"add"'
 *
 * 给定两个字符串 s 和 t ，判断它们是否是同构的。
 * 
 * 如果 s 中的字符可以按某种映射关系替换得到 t ，那么这两个字符串是同构的。
 * 
 * 
 * 每个出现的字符都应当映射到另一个字符，同时不改变字符的顺序。不同字符不能映射到同一个字符上，相同字符只能映射到同一个字符上，字符可以映射到自己本身。
 * 
 * 
 * 
 * 示例 1:
 * 
 * 
 * 输入：s = "egg", t = "add"
 * 输出：true
 * 
 * 
 * 示例 2：
 * 
 * 
 * 输入：s = "foo", t = "bar"
 * 输出：false
 * 
 * 示例 3：
 * 
 * 
 * 输入：s = "paper", t = "title"
 * 输出：true
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 
 * 
 * 1 <= s.length <= 5 * 10^4
 * t.length == s.length
 * s 和 t 由任意有效的 ASCII 字符组成
 * 
 * 
 */

// @lc code=start
class Solution {
public:
    bool isIsomorphic(string s, string t) {
        unordered_map<char, int> mp, cnt;
        for (int i = 0; i < s.size(); ++i) {
            char c1 = s[i], c2 = t[i];
            if (mp[c1 - 'a']) {
                if (mp[c1 - 'a'] != c2) {
                    return false;
                }
            } else {
                if (cnt[c2 - 'a']) {
                    return false;
                }
                mp[c1 - 'a'] = c2;
                cnt[c2 - 'a'] = 1;
            }
        }
        return true;
    }
};
// @lc code=end


int main() {
    Solution s;
    cout << s.isIsomorphic("badc", "baba") << endl;
    return 0;
}