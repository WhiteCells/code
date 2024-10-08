#include "../../head_file.h"

/*
problme: 

url: https://leetcode.cn/problems/maximum-rows-covered-by-columns/
 */

// TODO
class Solution {
public:
    int maximumRows(vector<vector<int>>& matrix, int numSelect) {
        int m = matrix.size();
        int n = matrix[0].size();
        vector<int> mask(m, 0);
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++){
                mask[i] += matrix[i][j] << (n - j - 1);
            }
        }
        int res = 0;
        int cur = 0;
        int limit = (1 << n);
        while ((++cur) < limit) {
            if (__builtin_popcount(cur) != numSelect) {
                continue;
            }
            int t = 0;
            for (int j = 0; j < m; j++) {
                if ((mask[j] & cur) == mask[j]) {
                    ++t;
                }
            }
            res = max(res, t);
        }
        return res;
    }
};

int main() {
    vector<vector<int>> matrix {
        {0,0,0},
        {1,0,1},
        {0,1,1},
        {0,0,1},
    };
    int numSelect = 2;
    // 输出：3
    cout << Solution().maximumRows(matrix, numSelect) << endl;
    return 0;
}