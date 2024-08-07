#include "../../head_file.h"

/*
problme:

url:
 */

class Solution {
public:
    vector<vector<int>> diagonalSort(vector<vector<int>> &mat) {
        /*
        00 01 02 03
        10 11 12 13
        20 21 22 23
         */
        /*
        {3,3,1,1},
        {2,2,1,2},
        {1,1,1,2}
         */
        int m = mat.size(), n = mat[0].size();
        // 遍历横向
        for (int i = 0; i < n; ++i) {
            int x = 0, y = i;
            vector<int> line;
            while (x < m && y < n) {
                line.push_back(mat[x][y]);
                ++x;
                ++y;
            }
            sort(line.begin(), line.end());
            x = 0, y = i;
            while (x < m && y < n) {
                mat[x][y] = line[x];
                ++x;
                ++y;
            }
        }
        // 便利纵向
        for (int j = 1; j < m; ++j) {
            int x = j, y = 0;
            vector<int> line;
            while (x < m && y < n) {
                line.push_back(mat[x++][y++]);
            }
            sort(line.begin(), line.end());
            x = j, y = 0;
            while (x < m && y < n) {
                mat[x][y] = line[y];
                ++x;
                ++y;
            }
        }
        return mat;
    }
};

int main() {
    vector<vector<int>> mat {{3,3,1,1}, // n - y < m
                             {2,2,1,2},
                             {1,1,1,2}};
    auto res = Solution().diagonalSort(mat);
    for (const auto v : res) {
        for (const auto ele : v) {
            cout << ele << " ";
        }
        cout << endl;
    }
    return 0;
}