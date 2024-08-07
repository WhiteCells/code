#include "../../head_file.h"

/*
problme: 1465. 切割后面积最大的蛋糕

矩形蛋糕的高度为 h 且宽度为 w，给你两个整数数组 horizontalCuts 和 verticalCuts，其中：

     horizontalCuts[i] 是从矩形蛋糕顶部到第  i 个水平切口的距离
    verticalCuts[j] 是从矩形蛋糕的左侧到第 j 个竖直切口的距离

请你按数组 horizontalCuts 和 verticalCuts 中提供的水平和竖直位置切割后，请你找出 面积最大 的那份蛋糕，并返回其 面积 。由于答案可能是一个很大的数字，因此需要将结果 对 109 + 7 取余 后返回。


示例 1：

输入：h = 5, w = 4, horizontalCuts = [1,2,4], verticalCuts = [1,3]
输出：4
解释：上图所示的矩阵蛋糕中，红色线表示水平和竖直方向上的切口。切割蛋糕后，绿色的那份蛋糕面积最大。

示例 2：

输入：h = 5, w = 4, horizontalCuts = [3,1], verticalCuts = [1]
输出：6
解释：上图所示的矩阵蛋糕中，红色线表示水平和竖直方向上的切口。切割蛋糕后，绿色和黄色的两份蛋糕面积最大。

示例 3：

输入：h = 5, w = 4, horizontalCuts = [3], verticalCuts = [3]
输出：9


提示：

    2 <= h, w <= 109
    1 <= horizontalCuts.length <= min(h - 1, 105)
    1 <= verticalCuts.length <= min(w - 1, 105)
    1 <= horizontalCuts[i] < h
    1 <= verticalCuts[i] < w
    题目数据保证 horizontalCuts 中的所有元素各不相同
    题目数据保证 verticalCuts 中的所有元素各不相同

url: https://leetcode.cn/problems/maximum-area-of-a-piece-of-cake-after-horizontal-and-vertical-cuts/description/
 */

// time complexity: O()
// spatial complexity: O()
// ERROR
class Solution1 {
public:
    int maxArea(int h, int w, vector<int> &horizontalCuts, vector<int> &verticalCuts) {
        int max_width = INT_MAX, max_height = INT_MAX;
        int y1 = 0, y2 = h;
        int x1 = 0, x2 = w;
        for (const auto &y : horizontalCuts) {
            max_height = min(max_height, max(y - y1, y2 - y));
            if (y <= y1 || y >= y2) {
                continue;
            }
            if (y - y1 <= (y2 - y1) / 2) {
                y1 = y;
            } else {
                y2 = y;
            }
        }
        for (const auto &x : verticalCuts) {
            max_width = min(max_width, max(x - x1, x2 - x));
            if (x <= x1 || x >= x2) {
                continue;
            }
            if (x - x1 <= (x2 - x1) / 2) {
                x1 = x;
            } else {
                x2 = x;
            }
        }
        return max_width * max_height % (int)(1e9 + 7);
    }
};

// time complexity: O(nlogn)
// spatial complexity: O(1)
class Solution2 {
public:
    int maxArea(int h, int w, vector<int>& horizontalCuts, vector<int>& verticalCuts) {
        static constexpr int mod = 1e9 + 7;
        sort(horizontalCuts.begin(), horizontalCuts.end());
        sort(verticalCuts.begin(), verticalCuts.end());
        long long max_width = verticalCuts[0], max_height = horizontalCuts[0];
        int v_sz = verticalCuts.size(), h_sz = horizontalCuts.size();
        for (int i = 1; i < v_sz; ++i) {
            max_width = max(max_width, (long long)verticalCuts[i] - verticalCuts[i - 1]);
        }
        max_width = max(max_width, (long long)w - verticalCuts[v_sz - 1]);
        for (int i = 1; i < h_sz; ++i) {
            max_height = max(max_height, (long long)horizontalCuts[i] - horizontalCuts[i - 1]);
        }
        max_height = max(max_height, (long long)h - horizontalCuts[h_sz - 1]);
        return max_height * max_width % mod;
    }
};

int main() {
    // h = 5, w = 4, horizontalCuts = [1,2,4], verticalCuts = [1,3]
    // int h = 5, w = 4;
    // vector<int> horizontalCuts { 1, 2, 4 };
    // vector<int> verticalCuts { 1, 3 };

    int h = 8, w = 5;
    vector<int> horizontalCuts { 5, 2, 6, 3 };
    vector<int> verticalCuts { 1, 4 };
    cout << Solution2().maxArea(h, w, horizontalCuts, verticalCuts) << endl;
    return 0;
}