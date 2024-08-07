#include <iostream>
#include <vector>

using namespace std;


class Solution {
public:
    int minFallingPathSum(vector<vector<int>>& matrix) {
        int n = matrix.size(), min_sum = INT_MAX;
        if (n == 1) {
            return matrix[0][0];
        }
        for (int i = 1; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (j == 0) {
                    matrix[i][j] = min(matrix[i - 1][j], matrix[i - 1][j + 1]) \
                        + matrix[i][j];
                }
                else if (j == n - 1) {
                    matrix[i][j] = min(matrix[i - 1][j], matrix[i - 1][j - 1]) \
                        + matrix[i][j];
                }
                else {
                    matrix[i][j] = min(min(matrix[i - 1][j - 1], matrix[i - 1][j + 1]), matrix[i - 1][j]) \
                        + matrix[i][j];
                }
                if (i == n - 1) {
                    min_sum = min(min_sum, matrix[i][j]);
                }
            }
        }
        return min_sum;
    }
};

int main() {
    Solution s;
    vector<vector<int>> matrix{
        { 2, 1, 3 },
        { 6, 5, 4 },
        { 7, 8, 9 }
    };
    cout << s.minFallingPathSum(matrix);
    return 0;
}