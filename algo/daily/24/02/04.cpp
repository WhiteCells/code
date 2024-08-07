#include "../../head_file.h"

/*
problme:
桌子上有一堆石头。
你们轮流进行自己的回合， 你作为先手 。
每一回合，轮到的人拿掉 1 - 3 块石头。

拿的时候剩余 1 个 赢
拿的时候剩余 2 个 赢
拿的时候剩余 3 个 赢
拿的时候剩余 4 个 输
拿的时候剩余 5 个 赢
拿的时候剩余 6 个 赢
拿的时候剩余 7 个 
拿掉最后一块石头的人就是获胜者。
url: https://leetcode.cn/problems/nim-game/
 */

class Solution {
public:
    bool canWinNim(int n) {
        return n % 4;
    }
};

int main() {
    cout << Solution().canWinNim(8) << endl;
    return 0;
}