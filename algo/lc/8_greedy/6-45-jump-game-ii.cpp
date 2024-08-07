#include "D:/distake/Coding/head_file.h"

/*
 * @Author: WhiteCells
 * @Date: 2023-05-19 21:53:44
 * @Last Modified by: WhiteCells
 * @Last Modified time: 2023-05-19 21:53:44
 * @Description: 45.跳跃游戏Ⅱ
 * https://leetcode.cn/problems/jump-game-ii/
*/

class Solution {
public:
    int jump(vector<int>& nums) {
        if (nums.size() == 1) {
            return 0;
        }
        int cnt = 0;  // 统计步数
        int cur = 0;  // 当前能到达的最大范围下标
        int next = 0; // 下一次能到达的最大范围下标
        for (int i = 0; i < nums.size(); ++i) {
            next = max(nums[i] + i, next);        // 更新下一次能到达的最大覆盖范围下标
            if (i == cur) {                       // 遇到当前覆盖的最远下标
                if (cur + 1 < nums.size()) {      // 当前最大覆盖范围下标不在终点
                    cnt++;                        // 向后走一步
                    cur = next;                   // 更新当前最大覆盖范围下标
                    if (next + 1 > nums.size()) { // 下一次最大范围下标已经超出终点，结束循环
                        break;
                    }
                }
                else {  // 当前最大范围下标已经可以到终点，结束循环
                    break;
                }
            }
        }
        return cnt;
    }
};

class Solution2 {
public:
    int jump(vector<int>& nums) {
        if (nums.size() == 1) {
            return 0;
        }
        int cnt = 0;  // 统计步数
        int cur = 0;  // 当前能到达的最大范围下标
        int next = 0; // 下一次能到达的最大范围下标
        for (int i = 0; i + 1 < nums.size(); ++i) {
            next = max(nums[i] + i, next); // 更新下一次能到达的最大范围下标
            if (cur == i) {                // 到了当前能到达的最大范围下标
                cnt++;                     // 向后走一步
                cur = next;                // 更新当前能走到的最大范围下标
            }
        }
        return cnt;
    }
};

class Solution3 {
public:
    int jump(vector<int>& nums) {
        int ans = 0;   // 统计步数
        int begin = 0; // 起点
        int end = 1;   // 能到达的终点（第一次为 1，for 左闭右开）
        while (end < nums.size()) {
            int maxPost = 0;
            for (int i = begin; i < end; ++i) {
                maxPost = max(nums[i] + i, maxPost); // 找最大能跳到的位置下标
            }
            ans++;
            begin = end;
            end = maxPost + 1;
        }
        return ans;
    }
};

int main() {
    // Solution s;
    // Solution2 s;
    Solution3 s;
    // vector<int> nums {1, 2};
    vector<int> nums {2, 3, 1, 1, 4};
    cout << s.jump(nums);
    return 0;
}