#include "../../head_file.h"

/*
problme: 849. 到最近的人的最大距离
给你一个数组 seats 表示一排座位，其中 seats[i] = 1 代表有人坐在第 i 个座位上，seats[i] = 0 代表座位 i 上是空的（下标从 0 开始）。
至少有一个空座位，且至少有一人已经坐在座位上。
亚历克斯希望坐在一个能够使他与离他最近的人之间的距离达到最大化的座位上。
返回他到离他最近的人的最大距离。
输入：seats = [1,0,0,0,1,0,1]
输出：2
解释：
如果亚历克斯坐在第二个空位（seats[2]）上，他到离他最近的人的距离为 2 。
如果亚历克斯坐在其它任何一个空位上，他到离他最近的人的距离为 1 。
因此，他到离他最近的人的最大距离是 2 。
提示：
    2 <= seats.length <= 2 * 104
    seats[i] 为 0 或 1
    至少有一个 空座位
    至少有一个 座位上有人
url: https://leetcode.cn/problems/maximize-distance-to-closest-person/
@Author: Eorys
@Date: 2023-08-22 06:33:29
@Last Modified by: Eorys
@Last Modified time: 2023-08-22 06:33:29
@Description:
*/

class Solution {
public:
    int maxDistToClosest(vector<int>& seats) {
        int res = 0, left = 0, right = 0, n = seats.size();
        // 统计从左至右的 0 的个数，如果左边连续 0 最长，直接坐在最左边
        while (left < n && 0 == seats[left]) {
            ++left;
        }
        res = max(res, left);
        while (left < n) {
            int right = left + 1;
            while (right < n && 0 == seats[right]) {
                ++right;
            }
            // right 到最后都是 0，直接坐最右边
            if (right == n) {
                res = max(res, right - left - 1);
            }
            // 此时需要坐在中间
            else {
                res = max(res, (right - left) / 2);
            }
            left = right;
        }
        return res;
    }
};

int main() {
    vector<int> seats { 1, 0, 0, 0, 1, 0, 1 };
    // vector<int> seats { 1, 0, 0, 0 };
    // vector<int> seats { 0, 0, 1 };
    Solution s;
    cout << s.maxDistToClosest(seats) << '\n';
    return 0;
}