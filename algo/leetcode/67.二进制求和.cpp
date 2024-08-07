#include "../head_file.h"
/*
 * @lc app=leetcode.cn id=67 lang=cpp
 *
 * [67] 二进制求和
 *
 * https://leetcode.cn/problems/add-binary/description/
 *
 * algorithms
 * Easy (52.93%)
 * Likes:    1135
 * Dislikes: 0
 * Total Accepted:    360.1K
 * Total Submissions: 680.5K
 * Testcase Example:  '"11"\n"1"'
 *
 * 给你两个二进制字符串 a 和 b ，以二进制字符串的形式返回它们的和。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入:a = "11", b = "1"
 * 输出："100"
 * 
 * 示例 2：
 * 
 * 
 * 输入：a = "1010", b = "1011"
 * 输出："10101"
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 <= a.length, b.length <= 10^4
 * a 和 b 仅由字符 '0' 或 '1' 组成
 * 字符串如果不是 "0" ，就不含前导零
 * 
 * 
 */

// @lc code=start
class Solution {
public:
    string addBinary(string a, string b) {
        reverse(a.begin(), a.end());
        reverse(b.begin(), b.end());
        int carry = 0;
        int n = max(a.size(), b.size());
        string res;
        for (int i = 0; i < n; ++i) {
            int now = 0;
            if (i < a.size()) {
                now += (a[i] - '0');
            }
            if (i < b.size()) {
                now += (b[i] - '0');
            }
            now += carry;
            if (now > 1) {
                carry = 1;
                res += (now % 2) + '0';
            } else {
                carry = 0;
                res += now + '0';
            }
        }
        if (carry) {
            res += '1';
        }
        reverse(res.begin(), res.end());
        return res;
    }
};
// @lc code=end

int main() {
    Solution s;
    cout << s.addBinary("1111", "1111") << endl;
    return 0;
}