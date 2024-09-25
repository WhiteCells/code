#include "../../head_file.h"

/*
problme:

url:
 */

class Solution
{
public:
    bool canMakeSquare(vector<vector<char>> &grid)
    {
        // 当 2 x 2 正方形中黑色和白色的个数相同时，无法通过修改一个颜色使之成为相同颜色的正方形
        int m = grid.size();
        int n = grid[0].size();
        for (int i = 0; i + 1 < m; ++i) {
            for (int j = 0; j + 1 < n; ++j) {
                int w = 0, b = 0;
                for (int k = i; k < i + 2; ++k) {
                    for (int h = j; h < j + 2; ++h) {
                        if ('W' == grid[k][h]) {
                            ++w;
                        }
                        else {
                            ++b;
                        }
                    }
                }
                std::cout << w << " " << b << std::endl;
                if (w != b) {
                    return true;
                }
            }
        }
        return false;
    }
};

int main()
{
    // [["B","W","B"],["B","W","W"],["B","W","W"]]
    vector<vector<char>> grid {{'B', 'W', 'B'},
                               {'W', 'B', 'W'},
                               {'B', 'W', 'B'}};
    cout << Solution().canMakeSquare(grid) << endl;
    return 0;
}