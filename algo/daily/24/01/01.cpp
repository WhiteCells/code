#include "../../head_file.h"

/*
problme:

url:
 */

class Solution {
public:
    int minOperationsMaxProfit(vector<int> &customers, int boardingCost, int runningCost) {
        int cur_profit = 0; // 当前利润
        int max_profit = 0; // 最大盈利
        int wait = 0; // 等待人数
        int t = -1; // 轮转次数
        int i = 0;
        // customers 遍历完后，需要考虑剩余的等待人数
        while (i < customers.size() || wait) {
            // 当前人数 = 上一次等待人数 + 新来的人数
            int cur = wait + (i < customers.size() ? customers[i] : 0);
            // 更新等待人数
            wait = max(cur - 4, 0);
            // 当前利润 += 当前可登舱人数 * 支付费用 - 运行成本
            cur_profit += min(cur, 4) * boardingCost - runningCost;
            // 当前利润为正则更新最大利润，并继续轮转
            if (cur_profit > max_profit) {
                max_profit = cur_profit;
                t = i + 1;
            }
            ++i;
        }
        return t;
    }
};

class Solution2 {
public:
    int minOperationsMaxProfit(vector<int> &customers, int boardingCost, int runningCost) {
        int wait = 0, turns = -1, max_profit = 0, cur_profit = 0;
        for (int i = 0; i < customers.size() || wait; ++i) {
            // 当前人数，上一次等待 + 新来的人数
            int cur = wait + (i < customers.size() ? customers[i] : 0);
            // 等待人数
            wait = max(cur - 4, 0);
            // 当前利润 = 当前可登舱人数 * 支付费用 - 运行成本
            cur_profit += min(cur, 4) * boardingCost - runningCost;
            // 更新最大利润，当前利润为正则继续轮转
            if (cur_profit > max_profit) {
                turns = i + 1;
                max_profit = cur_profit;
            }
        }
        return turns;
    }
};

int main() {
    // vector<int> customers {10, 9, 6};
    // int boardingCost = 6;
    // int runningCost = 4;
    // 7

    vector<int> customers {10, 10, 6, 4, 7};
    int boardingCost = 3;
    int runningCost = 8;
    // 9
    cout << Solution().minOperationsMaxProfit(customers, boardingCost, runningCost) << endl;
    return 0;
}