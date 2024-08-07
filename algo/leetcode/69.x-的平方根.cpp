#include "../head_file.h"
/*
 * @lc app=leetcode.cn id=69 lang=cpp
 *
 * [69] x 的平方根 
 *
 * https://leetcode.cn/problems/sqrtx/description/
 *
 * algorithms
 * Easy (38.45%)
 * Likes:    1486
 * Dislikes: 0
 * Total Accepted:    824K
 * Total Submissions: 2.1M
 * Testcase Example:  '4'
 *
 * 给你一个非负整数 x ，计算并返回 x 的 算术平方根 。
 * 
 * 由于返回类型是整数，结果只保留 整数部分 ，小数部分将被 舍去 。
 * 
 * 注意：不允许使用任何内置指数函数和算符，例如 pow(x, 0.5) 或者 x ** 0.5 。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：x = 4
 * 输出：2
 * 
 * 
 * 示例 2：
 * 
 * 
 * 输入：x = 8
 * 输出：2
 * 解释：8 的算术平方根是 2.82842..., 由于返回类型是整数，小数部分将被舍去。
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 0 <= x <= 2^31 - 1
 * 
 * 
 */

// @lc code=start
class Solution {
public:
    int mySqrt(int x) {
        long long i = 0, j = x;
        while (i <= j) {
            long long mid = i + ((j - i) >> 1);
            if (mid * mid >= x) {
                j = mid - 1;
            }
            else {
                i = mid + 1;
            }
        }
        return i * i == x ? i : i - 1;
    }
};
// @lc code=end


int main() {
    Solution s;
    cout << Solution().mySqrt(8) << endl;
    cout << Solution().mySqrt(9) << endl;
    cout << Solution().mySqrt(10) << endl;
    cout << Solution().mySqrt(6) << endl;
    cout << Solution().mySqrt(1) << endl;
    cout << Solution().mySqrt(2147395599) << endl;
    return 0;
}