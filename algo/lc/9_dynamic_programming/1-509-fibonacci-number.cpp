#include "D:/distake/Coding/head_file.h"

/*
 * @Author: WhiteCells
 * @Date: 2023-06-01 23:06:19
 * @Last Modified by: WhiteCells
 * @Last Modified time: 2023-06-01 23:06:19
 * @Description: 509. 斐波那契数
 * https://leetcode.cn/problems/fibonacci-number/
*/

class Solution {
public:
    int fib(int n) {
        if (n == 1 || n == 2) {
            return 1;
        }
        int a = 1;
        int b = 1;
        int c = 2;
        for (int i = 3; i < n; ++i) {
            a = b;
            b = c;
            c = a + b;
        }
        return c;
    }
};


int main() {
    Solution s;
    int n = 10;
    cout << s.fib(n);
    return 0;
}