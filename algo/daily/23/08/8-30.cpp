#include "../../head_file.h"

/*
problme: 1654. 到家的最少跳跃次数
有一只跳蚤的家在数轴上的位置 x 处。请你帮助它从位置 0 出发，到达它的家。
跳蚤跳跃的规则如下：
    它可以 往前 跳恰好 a 个位置（即往右跳）。
    它可以 往后 跳恰好 b 个位置（即往左跳）。
    它不能 连续 往后跳 2 次。
    它不能跳到任何 forbidden 数组中的位置。
跳蚤可以往前跳 超过 它的家的位置，但是它 不能跳到负整数 的位置。
给你一个整数数组 forbidden ，其中 forbidden[i] 是跳蚤不能跳到的位置，同时给你整数 a， b 和 x ，请你返回跳蚤到家的最少跳跃次数。如果没有恰好到达 x 的可行方案，请你返回 -1 。
url: https://leetcode.cn/problems/minimum-jumps-to-reach-home/description/
*/

class Solution {
public:
    int minimumJumps(vector<int>& forbidden, int a, int b, int x) {
        unordered_set<int> s(forbidden.begin(), forbidden.end());
        queue<tuple<int, int, bool>> q; // 当前位置 步数 是否后退
        q.emplace(0, 0, false);
        int idx = 0;
        while (!q.empty()) {
            auto [cur, step, isback] = q.front();
            q.pop();
            if (x == cur) {
                return step;
            }
            idx = cur + a; // 向前
            if (!s.count(idx) && idx < 6000) { // 新位置 且 不超过右边界
                q.emplace(idx, step + 1, false); // 标记为向前
                s.emplace(idx);
            }
            idx = cur - b; // 向后
            if (!isback && !s.count(idx) && idx >= 0) { // 新位置 且 不超过左边界
                q.emplace(idx, step + 1, true); // 标记为向后
            }
        }
        return -1;
    }
};

int main() {
    vector<int> forbidden { 1, 6, 2, 14, 5, 17, 4 };
    int a = 16, b = 9, x = 7;
    cout << Solution().minimumJumps(forbidden, a, b, x) << '\n';
    return 0;
}