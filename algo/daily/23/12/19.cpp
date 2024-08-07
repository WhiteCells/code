#include "../../head_file.h"

/*
problme:
输入: mat = [[10,20,15],[21,30,14],[7,16,32]]
输出: [1,1]
解释: 30 和 32 都是峰值，所以[1,1]和[2,2]都是可接受的答案。
url:
 */

class Solution {
public:
    vector<int> findPeakGrid(vector<vector<int>> &mat) {
        int i = 0, j = mat.size() - 2;
        while (i <= j) {
            int mid = j + ((i - j) >> 1);
            int idx = getMaxElementIndex(mat[mid]);
            if (mat[mid][idx] > mat[mid + 1][idx]) {
                j = mid - 1;
            } else {
                i = mid + 1;
            }
        }
        return {i, getMaxElementIndex(mat[i])};
    }
private:
    int getMaxElementIndex(vector<int> &v) {
        return max_element(v.begin(), v.end()) - v.begin();
    }
};

int main() {
    vector<vector<int>> mat {
        {10, 20, 15},
        {21, 30, 14},
        {7, 6, 32},
    };
    auto res = Solution().findPeakGrid(mat);
    // for (const auto &ele : res) {
    //     cout << ele << ' ';
    // }
    cout << endl;
    return 0;
}