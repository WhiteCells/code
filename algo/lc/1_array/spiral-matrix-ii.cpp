#include "../../head_file.h"

// 59.螺旋矩阵II
class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        if (n == 1) return vector<vector<int>>(1, vector<int>(1, 1));
        int count = 1;    // 初始化矩阵的数
        int offset = 1;   // 右边界的减少量
        int mid = n / 2;  // 为奇数时中间位置
        int loop = n / 2; // 循环次数
        int i = 0, j = 0; // 循环体内的循环变量
        int startx = 0, starty = 0; // 每一圈的起点位置
        vector<vector<int>> v(n, vector<int>(n));
        while (loop--) {
            i = startx;
            j = starty;

            // 模拟上行 从左到右
            for (j = starty; j < n - offset; ++j) {
                v[startx][j] = count++;
            }

            // 模拟右列 从上到下
            for (i = startx; i < n - offset; ++i) {
                v[i][j] = count++;
            }

            // 模拟下行 从右到左
            for (; j > starty; --j) {
                v[i][j] = count++;
            }

            // 模拟左列 从下到上
            for (; i > startx; --i) {
                v[i][j] = count++;
            }

            // 调整起始位置
            ++startx;
            ++starty;

            // 调整右边界
            ++offset;
        }
        // n 为奇数
        if (n % 2) {
            v[mid][mid] = count; // count 在上面循环中最后一次已经自增了一次
        }

        return v;
    }
};

int main() {
    Solution s;
    vector<vector<int>> v = s.generateMatrix(4);
    for (int i = 0; i < v.size(); ++i) {
        for (int j = 0; j < v[i].size(); ++j) {
            cout << v[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}