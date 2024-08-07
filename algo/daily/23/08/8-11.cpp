#include "../../head_file.h"

// https://leetcode.cn/problems/matrix-diagonal-sum/description/

// 输入：mat = [[1,2,3],
//             [4,5,6],
//             [7,8,9]]
// 输出：25
// 解释：对角线的和为：1 + 5 + 9 + 3 + 7 = 25
// 请注意，元素 mat[1][1] = 5 只会被计算一次。

class Solution {
public:
    int diagonalSum(vector<vector<int>>& mat) {
        int n = mat.size(), res = 0;
        for (int i = 0; i < n; ++i) {
            res += mat[i][i] + mat[i][n - 1 - i];
        }
        return n & 1 ? res - mat[n >> 1][n >> 1] : res;
    }
};

int main() {
    Solution s;
    auto mat = vector<vector<int>> {
        { 1, 2, 3 },
        { 4, 5, 6 },
        { 7, 8, 9 }
    };
    cout << s.diagonalSum(mat) << '\n';
    return 0;
}