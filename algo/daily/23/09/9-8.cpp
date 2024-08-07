#include "../../head_file.h"

/*
problme: 2651. 计算列车到站时间
输入：arrivalTime = 15, delayedTime = 5
输出：20
解释：列车正点到站时间是 15:00 ，延误 5 小时，所以列车实际到站的时间是 15 + 5 = 20（20:00）。
url: https://leetcode.cn/problems/calculate-delayed-arrival-time/
*/

class Solution {
public:
    int findDelayedArrivalTime(int arrivalTime, int delayedTime) {
        return arrivalTime % delayedTime;
    }
};

int main() {
    int arrivalTime = 15, delayedTime = 5;
    cout << Solution().findDelayedArrivalTime(arrivalTime, delayedTime) << '\n';
    return 0;
}