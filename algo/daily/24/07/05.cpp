#include "../../head_file.h"

/*
problme:

url:
 */

class Solution {
public:
    vector<vector<int>> modifiedMatrix(vector<vector<int>> &matrix) {
        int m = matrix.size(), n = matrix[0].size();
        unordered_map<int, int> mp;
        for (int i = 0; i < n; ++i) {
            int mx = matrix[0][i];
            for (int j = 0; j < m; ++j) {
                if (matrix[j][i] == -1) {
                    mp[j] = 1;
                }
                mx = max(mx, matrix[j][i]);
            }
            cout << mp.size() << endl;
            for (const auto &[j, _] : mp) {
                matrix[j][i] = mx;
            }
            mp.clear();
        }
        return matrix;
    }
};

int main() {
    vector<vector<int>> matrix = {
        {1,2,-1},
        {4,-1,6},
        {7,8,9}
    };
    auto res = Solution().modifiedMatrix(matrix);
    for (const auto &v : res) {
        for (const auto &ele : v) {
            cout << ele << " ";
        }
        cout << endl;
    }
    return 0;
}