#include "../../head_file.h"

/*
problme: 2731. 移动机器人

有一些机器人分布在一条无限长的数轴上，他们初始坐标用一个下标从 0 开始的整数数组 nums 表示。当你给机器人下达命令时，它们以每秒钟一单位的速度开始移动。

给你一个字符串 s ，每个字符按顺序分别表示每个机器人移动的方向。'L' 表示机器人往左或者数轴的负方向移动，'R' 表示机器人往右或者数轴的正方向移动。

当两个机器人相撞时，它们开始沿着原本相反的方向移动。

请你返回指令重复执行 d 秒后，所有机器人之间两两距离之和。由于答案可能很大，请你将答案对 109 + 7 取余后返回。

注意：

    对于坐标在 i 和 j 的两个机器人，(i,j) 和 (j,i) 视为相同的坐标对。也就是说，机器人视为无差别的。
    当机器人相撞时，它们 立即改变 它们的前进时间，这个过程不消耗任何时间。

    当两个机器人在同一时刻占据相同的位置时，就会相撞。

        例如，如果一个机器人位于位置 0 并往右移动，另一个机器人位于位置 2 并往左移动，下一秒，它们都将占据位置 1，并改变方向。再下一秒钟后，第一个机器人位于位置 0 并往左移动，而另一个机器人位于位置 2 并往右移动。

        例如，如果一个机器人位于位置 0 并往右移动，另一个机器人位于位置 1 并往左移动，下一秒，第一个机器人位于位置 0 并往左行驶，而另一个机器人位于位置 1 并往右移动。

示例 1：

输入：nums = [-2,0,2], s = "RLL", d = 3
输出：8
解释：
1 秒后，机器人的位置为 [-1,-1,1] 。现在下标为 0 的机器人开始往左移动，下标为 1 的机器人开始往右移动。
2 秒后，机器人的位置为 [-2,0,0] 。现在下标为 1 的机器人开始往左移动，下标为 2 的机器人开始往右移动。
3 秒后，机器人的位置为 [-3,-1,1] 。
下标为 0 和 1 的机器人之间距离为 abs(-3 - (-1)) = 2 。
下标为 0 和 2 的机器人之间的距离为 abs(-3 - 1) = 4 。
下标为 1 和 2 的机器人之间的距离为 abs(-1 - 1) = 2 。
所有机器人对之间的总距离为 2 + 4 + 2 = 8 。

示例 2：

输入：nums = [1,0], s = "RL", d = 2
输出：5
解释：
1 秒后，机器人的位置为 [2,-1] 。
2 秒后，机器人的位置为 [3,-2] 。
两个机器人的距离为 abs(-2 - 3) = 5 。


提示：

    2 <= nums.length <= 105
    -2 * 109 <= nums[i] <= 2 * 109
    0 <= d <= 109
    nums.length == s.length
    s 只包含 'L' 和 'R' 。
    nums[i] 互不相同。


url: https://leetcode.cn/problems/movement-of-robots/description/
 */

// TLE
// time complexity: O(n2)
// spatial complexity: O(1)
// 不必关注方向问题, 只需按照原方向移动即可
class Solution1 {
public:
    int sumDistance(vector<int> &nums, string s, int d) {
        static constexpr int mod = 1e9 + 7;
        int n = nums.size();
        for (int t = 0; t < d; ++t) {
            for (int i = 0; i < n; ++i) {
                nums[i] += ('R' == s[i] ? 1 : -1); // L -> -1, R -> +1
            }
        }
        long long res = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                res += abs(nums[i] % mod - nums[j] % mod);
            }
        }
        return res % mod;
    }
};

// time complexity: O(nlogn)
// spatial complexity: O(1)
class Solution2 {
public:
    int sumDistance(vector<int> &nums, string s, int d) {
        static constexpr int mod = 1e9 + 7;
        int n = nums.size();
        for (int i = 0; i < n; ++i) {
            nums[i] += ('R' == s[i] ? d : -d); // L -> -d, R -> +d
        }
        long long res = 0;
        sort(nums.begin(), nums.end());
        for (int i = 1; i < n; ++i) {
            // 从小到大枚举 nums
            // 遍历到 i, i 左边有 i 个数, 右边(包括 nums[i])有 n - i 个数, 总共有 i * (n - i) 对数 在重复计算 (nums[i] - nums[i - 1])
            res += ((long long)nums[i] - (long long)nums[i - 1]) * i % mod * (n - i) % mod;
        }
        return res % mod;
    }
};

int main() {
    vector<int> nums { -2, 0, 2 };
    string s = "RLL";
    int d = 3;
    // cout << Solution1().sumDistance(nums, s, d);
    cout << Solution2().sumDistance(nums, s, d);
    return 0;
}