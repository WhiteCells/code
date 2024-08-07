#include "D:/distake/Coding/head_file.h"


class Solution {
private:
    vector<vector<string>> res;

    /// @brief 判断 Q 的位置是否有效
    /// @param row Q 所在的行
    /// @param col Q 所在的列
    /// @param n 棋盘大小
    /// @param ans 已知棋盘
    /// @return 有效返回 true，无效返回 false
    bool isValid(int row, int col, int n, vector<string>& ans) {
        // 同一行上不能有 Q，实际不会有同行的，因为在递归的时候每次只在一行中选中一个位置

        // 同一列上不能有 Q
        for (int i = 0; i < row; ++i) {
            if (ans[i][col] == 'Q') {
                return false;
            }
        }

        // 左斜线上不能有 Q
        for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; --i, --j) {
            if (ans[i][j] == 'Q') {
                return false;
            }
        }

        // 右斜线上不能有 Q
        for (int i = row - 1, j = col + 1; i >= 0 && j < n; --i, ++j) {
            if (ans[i][j] == 'Q') {
                return false;
            }
        }
        return true;
    }

    /// @brief 深度优先搜索
    /// @param n 棋盘大小
    /// @param row 当前遍历到的棋盘行数
    /// @param ans 每一种情况的容器
    void dfs(int n, int row, vector<string>& ans) {
        /* 递归终止条件：遍历的行数 row 到了棋盘的最大行数 n */
        if (n == row) { // row 从 0 开始
            res.push_back(ans);
            return;
        }

        for (int col = 0; col < n; ++col) {
            if (isValid(row, col, n, ans)) {
                ans[row][col] = 'Q';
                dfs(n, row + 1, ans);
                ans[row][col] = '.';
            }
        }
    }
public:
    vector<vector<string>> solveNQueens(int n) {
        vector<string> ans(n, string(n, '.'));
        dfs(n, 0, ans);
        return res;
    }
};


int main() {
    Solution s;
    vector<vector<string>> res = s.solveNQueens(5);
    for (const auto& v : res) {
        for (const auto& s : v) {
            cout << s << '\n';
        }
    }
    return 0;
}