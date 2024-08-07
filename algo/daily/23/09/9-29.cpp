#include "../../head_file.h"

/*
problme: 605. 种花问题

假设有一个很长的花坛，一部分地块种植了花，另一部分却没有。可是，花不能种植在相邻的地块上，它们会争夺水源，两者都会死去。

给你一个整数数组 flowerbed 表示花坛，由若干 0 和 1 组成，其中 0 表示没种植花，1 表示种植了花。另有一个数 n ，能否在不打破种植规则的情况下种入 n 朵花？能则返回 true ，不能则返回 false 。


示例 1：

输入：flowerbed = [1,0,0,0,1], n = 1
输出：true

示例 2：

输入：flowerbed = [1,0,0,0,1], n = 2
输出：false


提示：

    1 <= flowerbed.length <= 2 * 104
    flowerbed[i] 为 0 或 1
    flowerbed 中不存在相邻的两朵花
    0 <= n <= flowerbed.length

url: https://leetcode.cn/problems/can-place-flowers/description/
 */

class Solution {
public:
    bool canPlaceFlowers(vector<int> &flowerbed, int n) {
        int f_sz = flowerbed.size();
        if (1 == f_sz && 1 == n && 0 == flowerbed[0]) {
            return true;
        }
        for (int i = 0; i < f_sz; ++i) {
            if (0 == flowerbed[i]) {
                // 左端
                if (0 == i && f_sz > i + 1 && 0 == flowerbed[i + 1]) {
                    --n;
                    flowerbed[i] = 1;
                }
                // 中间
                if (0 < i && f_sz > i + 1 && 0 == flowerbed[i - 1] && 0 == flowerbed[i + 1]) {
                    --n;
                    flowerbed[i] = 1;
                }
                // 右端
                if (f_sz - 1 == i && 0 < i - 1 && 0 == flowerbed[i - 1]) {
                    --n;
                    flowerbed[i] = 1;
                }
            }
        }
        return 0 >= n; // 可能能种的花比 n 大
    }
};

// 防御式编程思想
// 两端加上 0 ，使得不用考虑边界
class Solution2 {
public:
    bool canPlaceFlowers(vector<int> &flowerbed, int n) {
        flowerbed.insert(flowerbed.begin(), { 0 });
        flowerbed.insert(flowerbed.end(), { 0 });
        for (int i = 1; i + 1 < flowerbed.size(); ++i) {
            if (0 == flowerbed[i - 1] && 0 == flowerbed[i] && 0 == flowerbed[i + 1]) {
                flowerbed[i] = 1;
                --n;
            }
        }
        return 0 >= n;
    }
};

int main() {
    vector<int> v{ 1, 0, 0, 0, 1 };
    int n = 1;
    cout << Solution().canPlaceFlowers(v, n) << '\n';
    vector<int> v2{ 1, 0, 0, 0, 1 };
    int n2 = 1;
    cout << Solution2().canPlaceFlowers(v2, n2) << '\n';
    return 0;
}