#include "../../head_file.h"

/*
problme:
给你一个下标从 0 开始的整数数组 arr 和一个 m x n 的整数 矩阵 mat 。arr 和 mat 都包含范围 [1，m * n] 内的 所有 整数。

从下标 0 开始遍历 arr 中的每个下标 i ，并将包含整数 arr[i] 的 mat 单元格涂色。

请你找出 arr 中在 mat 的某一行或某一列上都被涂色且下标最小的元素，并返回其下标 i 。
url: https://leetcode.cn/problems/first-completely-painted-row-or-column/description/
 */

class Solution {
public:
    int firstCompleteIndex(vector<int> &arr, vector<vector<int>> &mat) {
        int m = mat.size(), n = mat[0].size();
        vector<int> vy(n), vx(m);
        unordered_map<int, pair<int, int>> mp; // mat[i][j] : <i, j>
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                mp[mat[i][j]] = make_pair(i, j);
            }
        }
        int res = 0;
        for (int i = 0; i < arr.size(); ++i) {
            auto &[x, y] = mp[arr[i]];
            vy[y]++;
            vx[x]++;
            if (vy[y] == m || vx[x] == n) {
                res = i;
                break;
            }
        }
        return res;
    }
};


int main() {
    // vector<int> arr {1,3,4,2};
    // vector<vector<int>> mat {
    //     {1, 4},
    //     {2, 3},
    // };
    vector<int> arr {6, 2, 3, 1, 4, 5};
    vector<vector<int>> mat {
        {5, 1},
        {2, 4},
        {6, 3}
    };
    cout << Solution().firstCompleteIndex(arr, mat) << endl;
    return 0;
}