#include "D:/distake/Coding/head_file.h"


class Solution {
private:
    /* 有效性检验函数：i，数的行；j，数的列；board，数独的分布 */
    bool isValid(int i, int j, char c, vector<vector<char>>& board) {
        // 判断同一行是否重复出现 c
        for (int k = 0; k < board[0].size(); ++k) {
            if (board[i][k] == c) {
                return false;
            }
        }
        // 判断同一列是否重复出现 c
        for (int k = 0; k < board.size(); ++k) {
            if (board[k][j] == c) {
                return false;
            }
        }
        // 3*3 九宫格内是否重复出现 c
        int row = (i / 3) * 3;
        int col = (j / 3) * 3;
        for (int m = row; m < row + 3; ++m) {
            for (int n = col; n < col + 3; ++n) {
                if (board[m][n] == c) {
                    return false;
                }
            }
        }
        return true;
    }
    /* 递归参数：board，数独的分布
       递归返回值：bool，因为找到一个符合条件，就立即返回 */
    bool dfs(vector<vector<char>>& board) {
        for (int i = 0; i < board.size(); ++i) {         // 遍历行
            for (int j = 0; j < board[0].size(); ++j) {  // 遍历列
                if (board[i][j] == '.') {                // 但前位置非空
                    for (char c = '1'; c <= '9'; ++c) {  // '1'~'9' 一个一个试
                        if (isValid(i, j, c, board)) {   // 当前位置 c 是否合适
                            board[i][j] = c;
                            if (dfs(board)) {
                                return true;
                            }
                            board[i][j] = '.';
                        }
                    }
                    return false; // 都试过，都无效，返回 false
                }
            }
        }
        return true; // 遍历完没有返回 false，返回 true
    }
public:
    void solveSudoku(vector<vector<char>>& board) {
        dfs(board);
    }
};

class Solution2 {
private:
    /* */
    bool isValid(int i, int j, char c, vector<vector<char>>& board) {
        // 检测行
        for (int col = 0; col < board[0].size(); ++col) {
            if (board[i][col] == c) {
                return false;
            }
        }
        // 检测列
        for (int row = 0; row < board.size(); ++row) {
            if (board[row][j] == c) {
                return false;
            }
        }
        // 检测九宫格
        int rowStart = (i / 3) * 3;
        int colStart = (j / 3) * 3;
        for (int row = rowStart; row < rowStart + 3; ++row) {
            for (int col = colStart; col < colStart + 3; ++col) {
                if (board[row][col] == c) {
                    return false;
                }
            }
        }
        return true;
    }
    bool dfs(int row, int col, vector<vector<char>>& board) {
        for (int i = row; i < board.size(); ++i) {
            for (int j = col; j < board[0].size(); ++j) {
                if (board[i][j] == '.') {
                    for (char c = '1'; c <= '9'; ++c) {
                        if (isValid(i, j, c, board)) {
                            board[i][j] = c;
                            if (dfs(row, col + 1, board)) {
                                return true;
                            }
                            board[i][j] = '.';
                        }
                    }
                    return false;
                }
            }
            col = 0;
        }
        return true;
    }
public:
    void solveSudoku(vector<vector<char>>& board) {
        dfs(0, 0, board);
    }
};


int main() {
    vector<vector<char>> board {
        { '5', '3', '.', '.', '7', '.', '.', '.', '.' },
        { '6', '.', '.', '1', '9', '5', '.', '.', '.' },
        { '.', '9', '8', '.', '.', '.', '.', '6', '.' },
        { '8', '.', '.', '.', '6', '.', '.', '.', '3' },
        { '4', '.', '.', '8', '.', '3', '.', '.', '1' },
        { '7', '.', '.', '.', '2', '.', '.', '.', '6' },
        { '.', '6', '.', '.', '.', '.', '2', '8', '.' },
        { '.', '.', '.', '4', '1', '9', '.', '.', '5' },
        { '.', '.', '.', '.', '8', '.', '.', '7', '9' }
    };
    // Solution s;
    // s.solveSudoku(board);
    Solution2 s;
    s.solveSudoku(board);
    for (const auto& v : board) {
        for (const auto& c : v) {
            cout << c << " ";
        }
        cout << '\n';
    }
    return 0;
}