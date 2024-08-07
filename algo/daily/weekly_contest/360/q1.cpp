#include "../../head_file.h"

/*
problme: 2833. 距离原点最远的点
给你一个长度为 n 的字符串 moves ，该字符串仅由字符 'L'、'R' 和 '_' 组成。字符串表示你在一条原点为 0 的数轴上的若干次移动。
你的初始位置就在原点（0），第 i 次移动过程中，你可以根据对应字符选择移动方向：
    如果 moves[i] = 'L' 或 moves[i] = '_' ，可以选择向左移动一个单位距离
    如果 moves[i] = 'R' 或 moves[i] = '_' ，可以选择向右移动一个单位距离
移动 n 次之后，请你找出可以到达的距离原点 最远 的点，并返回 从原点到这一点的距离 。
url: https://leetcode.cn/problems/furthest-point-from-origin/
*/

class Solution {
public:
    int furthestDistanceFromOrigin(string moves) {
        int space = 0, left = 0, right = 0;
        for (const auto& c : moves) {
            switch (c) {
                case '_':
                    ++space;
                    break;
                case 'L':
                    ++left;
                    break;
                case 'R':
                    ++right;
                    break;
            }
        }
        return (left > right ? left - right : right - left) + space;
    }
};

int main() {
    string moves = "_R__LL_";
    cout << Solution().furthestDistanceFromOrigin(moves) << '\n';
    return 0;
}