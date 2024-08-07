#include "../head_file.h"
/*
 * @lc app=leetcode.cn id=119 lang=cpp
 *
 * [119] 杨辉三角 II
 *
 * https://leetcode.cn/problems/pascals-triangle-ii/description/
 *
 * algorithms
 * Easy (68.92%)
 * Likes:    522
 * Dislikes: 0
 * Total Accepted:    291.7K
 * Total Submissions: 423.2K
 * Testcase Example:  '3'
 *
 * 给定一个非负索引 rowIndex，返回「杨辉三角」的第 rowIndex 行。
 * 
 * 在「杨辉三角」中，每个数是它左上方和右上方的数的和。
 * 
 * 
 * 
 * 
 * 
 * 示例 1:
 * 
 * 
 * 输入: rowIndex = 3
 * 输出: [1,3,3,1]
 * 
 * 
 * 示例 2:
 * 
 * 
 * 输入: rowIndex = 0
 * 输出: [1]
 * 
 * 
 * 示例 3:
 * 
 * 
 * 输入: rowIndex = 1
 * 输出: [1,1]
 * 
 * 
 * 
 * 
 * 提示:
 * 
 * 
 * 0 
 * 
 * 
 * 
 * 
 * 进阶：
 * 
 * 你可以优化你的算法到 O(rowIndex) 空间复杂度吗？
 * 
 */

// @lc code=start
// class Solution {
// public:
//     vector<int> getRow(int rowIndex) {
//         vector<int> res(rowIndex + 1, 1);
//         for (int i = 1, tmp = rowIndex - 1; i <= rowIndex / 2; ++i, --tmp) {
//             res[i] = tmp + res[i - 1];
//         }
//         for (int i = rowIndex, j = 0; i > rowIndex / 2; --i, ++j) {
//             res[i] = res[j];
//         }
//         return res;
//     }
// };

class Solution {
public:
    vector<int> getRow(int rowIndex) {
        vector<vector<int>> res(rowIndex + 1, vector<int>(rowIndex + 1, 1));
        for (int row = 2; row <= rowIndex; ++row) {
            for (int col = 1; col < row; ++col) {
                res[row][col] = res[row - 1][col] + res[row - 1][col - 1];
            }
        }
        return res[rowIndex];
    }
};
// @lc code=end


int main() {
    Solution s;
    auto res = s.getRow(5);
    for (const auto &e : res) {
        cout << e << ' ';
    }
    return 0;
}