#include "../../head_file.h"

/*
problme: 2235. 两整数相加
给你两个整数 num1 和 num2，返回这两个整数的和。
提示：
    -100 <= num1, num2 <= 100
url: https://leetcode.cn/problems/add-two-integers/description/
@Author: Eorys
@Date: 2023-08-19 06:11:13
@Last Modified by: Eorys
@Last Modified time: 2023-08-19 06:11:13
@Description:
*/

class Solution {
public:
    int sum(int num1, int num2) {
        // return num1 + num2;

        // while (num2) {
        //     int n = num1 ^ num2;
        //     num2 &= num1;
        //     num2 <<= 1;
        //     num1 = n;
        // }
        // return num1;

        // 半加器，数值相同且为 1，进行一次进位
        // 把数拆分成未进位数和进位数，再进行运算，实现循环进位，直到没有进位
        return num2 ? sum(num1 ^ num2, (num1 & num2) << 1) : num1;
    }
};


int main() {
    int num1 = 10, num2 = 7;
    Solution s;
    cout << s.sum(num1, num2) << '\n';
    return 0;
}