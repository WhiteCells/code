/*
 * @lc app=leetcode.cn id=14 lang=cpp
 *
 * [14] 最长公共前缀
 *
 * https://leetcode.cn/problems/longest-common-prefix/description/
 *
 * algorithms
 * Easy (43.45%)
 * Likes:    2868
 * Dislikes: 0
 * Total Accepted:    1.1M
 * Total Submissions: 2.6M
 * Testcase Example:  '["flower","flow","flight"]'
 *
 * 编写一个函数来查找字符串数组中的最长公共前缀。
 *
 * 如果不存在公共前缀，返回空字符串 ""。
 *
 *
 *
 * 示例 1：
 *
 *
 * 输入：strs = ["flower","flow","flight"]
 * 输出："fl"
 *
 *
 * 示例 2：
 *
 *
 * 输入：strs = ["dog","racecar","car"]
 * 输出：""
 * 解释：输入不存在公共前缀。
 *
 *
 *
 * 提示：
 *
 *
 * 1 <= strs.length <= 200
 * 0 <= strs[i].length <= 200
 * strs[i] 仅由小写英文字母组成
 *
 *
 */
#include "../head_file.h"
// @lc code=start
class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        if (0 == strs.size()) {
            return "";
        }
        string res;
        sort(strs.begin(), strs.end());
        string a = strs.front();
        string b = strs.back();
        for (int i = 0; i < a.size(); ++i) {
            if (a[i] == b[i]) {
                res += a[i];
            }
            else {
                break;
            }
        }
        return res;
    }
};
// @lc code=end

int main(int argc, char const *argv[]) {
    vector<string> strs { "flower", "flow", "flight" };
    Solution s;
    cout << s.longestCommonPrefix(strs) << '\n';
    return 0;
}
