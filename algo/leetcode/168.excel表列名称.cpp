#include "../head_file.h"
/*
 * @lc app=leetcode.cn id=168 lang=cpp
 *
 * [168] Excel表列名称
 *
 * https://leetcode.cn/problems/excel-sheet-column-title/description/
 *
 * algorithms
 * Easy (44.22%)
 * Likes:    662
 * Dislikes: 0
 * Total Accepted:    147.5K
 * Total Submissions: 333.6K
 * Testcase Example:  '1'
 *
 * 给你一个整数 columnNumber ，返回它在 Excel 表中相对应的列名称。
 *
 * 例如：
 *
 *
 * A -> 1
 * B -> 2
 * C -> 3
 * ...
 * Z -> 26
 * AA -> 27
 * AB -> 28
 * ...
 *
 *
 *
 *
 * 示例 1：
 *
 *
 * 输入：columnNumber = 1
 * 输出："A"
 *
 *
 * 示例 2：
 *
 *
 * 输入：columnNumber = 28
 * 输出："AB"
 *
 *
 * 示例 3：
 *
 *
 * 输入：columnNumber = 701
 * 输出："ZY"
 *
 *
 * 示例 4：
 *
 *
 * 输入：columnNumber = 2147483647
 * 输出："FXSHRXW"
 *
 *
 *
 *
 * 提示：
 *
 *
 * 1
 *
 *
 */

// @lc code=start
class Solution {
public:
    string convertToTitle(int num) {
        string res;
        while (num) {
            res += (num - 1) % 26 + 'A';
            num = (num - 1) / 26;
        }
        reverse(res.begin(), res.end());
        return res;
    }
};
// @lc code=end

int main() {
    Solution s;
    cout << Solution().convertToTitle(26) << endl;
    cout << Solution().convertToTitle(27) << endl;
    cout << Solution().convertToTitle(28) << endl;
    cout << Solution().convertToTitle(701) << endl;
    cout << Solution().convertToTitle(2147483647) << endl;
    return 0;
}