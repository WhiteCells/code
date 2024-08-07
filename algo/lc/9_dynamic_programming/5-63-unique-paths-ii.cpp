#include "D:/distake/Coding/head_file.h"

/*
 * @Author: WhiteCells
 * @Date: 2023-06-07 17:56:20
 * @Last Modified by: WhiteCells
 * @Last Modified time: 2023-06-07 17:56:20
 * @Description:
*/

class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        for (int i = 0; i < obstacleGrid.size(); ++i) { // 0 列
            if (obstacleGrid[i][0] == 1) {
                for (int ii = i; ii < obstacleGrid.size(); ++ii) {
                    obstacleGrid[ii][0] = 0;
                }
                break;
            }
            else {
                obstacleGrid[i][0] = 1;
            }
        }
        for (int j = 0; j < obstacleGrid[0].size(); ++j) { // 0 行
            if (obstacleGrid[0][j] == 1) {
                for (int jj = j; jj < obstacleGrid[0].size(); ++jj) {
                    obstacleGrid[0][jj] = 0;
                }
                break;
            }
            else {
                obstacleGrid[0][j] = 1;
            }
        }
        for (int i = 1; i < obstacleGrid.size(); ++i) { // 行
            for (int j = 1; j < obstacleGrid[0].size(); ++j) { // 列
                if (obstacleGrid[i][j] == 1) {
                    obstacleGrid[i][j] = 0;
                }
                else {
                    obstacleGrid[i][j] = obstacleGrid[i - 1][j] + obstacleGrid[i][j - 1];
                }
            }
        }
        return obstacleGrid[obstacleGrid.size() - 1][obstacleGrid[0].size() - 1];
    }
};


class Solution2 {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        vector<vector<int>> dp(obstacleGrid.size(), vector<int>(obstacleGrid[0].size(), 0));
        for (int j = 0; j < dp[0].size() && obstacleGrid[0][j] == 0; ++j) { // 0 行操作
            dp[0][j] = 1;
        }
        for (int i = 0; i < dp.size() && obstacleGrid[i][0] == 0; ++i) { // 0 列操作
            dp[i][0] = 1;
        }
        for (int i = 1; i < dp.size(); ++i) {
            for (int j = 1; j < dp[0].size(); ++j) {
                if (obstacleGrid[i][j] == 1) {
                    continue;
                }
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
            }
        }
        return dp[dp.size() - 1][dp[0].size() - 1];
    }
};

class Solution3 {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        for (int i = 0; i < obstacleGrid.size(); ++i) {
            if (obstacleGrid[i][0] == 1) {
                for (int ii = i; ii < obstacleGrid.size(); ++ii) {
                    obstacleGrid[ii][0] = 0;
                }
                break;
            }
            obstacleGrid[i][0] = 1;
        }
        for (int j = 1; j < obstacleGrid[0].size(); ++j) {
            if (obstacleGrid[0][j] == 1) {
                for (int jj = j; jj < obstacleGrid[0].size(); ++jj) {
                    obstacleGrid[0][jj] = 0;
                }
                break;
            }
            obstacleGrid[0][j] = 1;
        }
        for (int i = 1; i < obstacleGrid.size(); ++i) {
            for (int j = 1; j < obstacleGrid[0].size(); ++j) {
                if (obstacleGrid[i][j] == 1) {
                    obstacleGrid[i][j] = 0;
                }
                else {
                    obstacleGrid[i][j] = obstacleGrid[i - 1][j] + obstacleGrid[i][j - 1];
                }
            }
        }
        return obstacleGrid[obstacleGrid.size() - 1][obstacleGrid[0].size() - 1];
    }
};

int main() {
    Solution s;
    Solution2 s2;
    Solution3 s3;
    vector<vector<int>> obstacleGrid {{0, 0, 0}, { 0, 1, 0 }, { 0, 0, 0 }};
    // vector<vector<int>> obstacleGrid {{0, 1}, { 0, 0 }};
    // cout << s.uniquePathsWithObstacles(obstacleGrid);
    // cout << s2.uniquePathsWithObstacles(obstacleGrid);
    cout << s3.uniquePathsWithObstacles(obstacleGrid);
    return 0;
}