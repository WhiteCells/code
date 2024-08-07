#include "../../head_file.h"

/*
problme:

url:
 */

class Solution {
public:
    bool areSimilar(vector<vector<int>> &mat, int k) {
        int n = mat.size();
        int m = mat[0].size();
        vector<vector<int>> tmp(n, vector<int>(m));
        k %= m;
        for (int i = 0; i < n; ++i) {
            if (i & 1) {
                // 偶数行, 向左移动 k
                for (int j = 0; j < m - k; ++j) {
                    tmp[i][j] = mat[i][j + k];
                }
                for (int j = m - k, jj = 0; j < m; ++j) {
                    tmp[i][j] = mat[i][jj++];
                }
            } else {
                // 奇数行, 向右移动 k
                for (int j = k, jj = 0; j < m; ++j) {
                    tmp[i][j] = mat[i][jj++];
                }
                for (int j = 0; j < k; ++j) {
                    tmp[i][j] = mat[i][m - k + j];
                }
            }
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (tmp[i][j] != mat[i][j]) {
                    return false;
                }
            }
        }
        return true;
    }
};

int main() {
    vector<vector<int>> mat {
        {1, 2, 1, 2},
        {5, 5, 5, 5},
        {6, 3, 6, 3},
    };
    int k = 2;
    cout << Solution().areSimilar(mat, k) << endl;
    return 0;
}