#include "D:/distake/Coding/head_file.h"

/*
 * @Author: WhiteCells
 * @Date: 2023-05-19 21:52:21
 * @Last Modified by: WhiteCells
 * @Last Modified time: 2023-05-19 21:52:21
 * @Description: 55.跳跃游戏
 * https://leetcode.cn/problems/jump-game/
*/

class Solution {
public:
    bool canJump(vector<int>& nums) {
        if (nums.size() == 1) {
            return true;
        }
        int step = 1; // 需要的步数
        for (int i = nums.size() - 2; i >= 0; --i) { // 从倒数第二个开始向后看
            if (nums[i] >= step) {
                step = 1; // 截断后面数，从 i 到 i - 1 上的步数需要 1
            }
            else {
                ++step; // 从 i 个 到 (nums.size()-1) 需要的步数加 1
            }
            if (i == 0 && step > 1) { // 到了第一个，需要的步数不为 1
                return false;
            }
        }
        return true;
    }
};

int main() {
    Solution s;

    return 0;
}