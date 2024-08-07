#include "../../head_file.h"

/*
 * @Author: Eorys
 * @Date: 2023-07-22 12:31:21
 * @Last Modified by: Eorys
 * @Last Modified time: 2023-07-22 12:31:21
 * @Description:
 *在柠檬水摊上，每一杯柠檬水的售价为 5 美元。顾客排队购买你的产品，
（按账单 bills 支付的顺序）一次购买一杯。
每位顾客只买一杯柠檬水，然后向你付 5 美元、10 美元或 20 美元。
你必须给每个顾客正确找零，也就是说净交易是每位顾客向你支付 5 美元。
注意，一开始你手头没有任何零钱。
给你一个整数数组 bills ，其中 bills[i] 是第 i 位顾客付的账。如果你能给每位顾客正确找零，返回 true ，否则返回 false 。

*/

class Solution {
public:
    bool lemonadeChange(vector<int>& bills) {
        int income[2]{}; // 0-5 1-10，20块 不参与找零
        for (const auto& bill : bills) {
            // 5块 直接计入
            if (5 == bill) {
                ++income[0];
            }
            else if (10 == bill) {
                // 没有 5块
                if (!income[0]) {
                    return false;
                }
                --income[0], ++income[1];
            }
            else {
                // 5块 和 10块同时有，优先使用
                if (income[0] && income[1]) {
                    --income[1], --income[0];
                }
                // 只有 5块
                else if (!income[1] && income[0] >= 3) {
                    income[0] -= 3;
                }
                else {
                    return false;
                }
            }
        }
        return true;
    }
};


int main() {
    Solution s;
    auto bills = vector<int>{ 5, 5, 5, 10, 20 };
    cout << s.lemonadeChange(bills);
    return 0;
}