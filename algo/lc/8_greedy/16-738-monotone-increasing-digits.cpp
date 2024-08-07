#include "D:/distake/Coding/head_file.h"

/*
 * @Author: WhiteCells
 * @Date: 2023-05-29 17:41:08
 * @Last Modified by: WhiteCells
 * @Last Modified time: 2023-05-29 17:41:08
 * @Description: 738. 单调递增的数字
 * https://leetcode.cn/problems/monotone-increasing-digits/
 * 输入: n = 10
 * 输出: 9
*/

class Solution {
private:
    bool isIncreasingDigits(int num) { // num 只可能是两位数
        int pre = num % 10;
        num /= 10;
        while (num) {
            if (num % 10 > pre) {
                return false;
            }
            pre = num % 10;
            num /= 10;
        }
        return true;
    }
public:
    int monotoneIncreasingDigits(int n) {
        if (n >= 0 && n <= 9) {
            return n;
        }
        for (int i = n; i >= 0; --i) {
            if (isIncreasingDigits(i)) {
                return i;
            }
        }
        return 0;
    }
};


class Solution2 {
public:
    int monotoneIncreasingDigits(int n) {
        string num = to_string(n);
        int flag = 0;
        for (int i = num.size() - 1; i >= 1; --i) {
            if (num[i] < num[i - 1]) {
                flag = i;
                --num[i - 1];
            }
        }
        for (int i = flag; i < num.size(); ++i) {
            num[i] = '9';
        }
        return stoi(num);
    }
};

class Solution3 {
public:
    int monotoneIncreasingDigits(int n) {
        int i = 1;
        int res = n;
        while (i <= res / 10) {
            int n = res / i % 100; // 每次取两个位
            i *= 10;
            if (n / 10 > n % 10) // 比较的高一位大于底一位
                res = res / i * i - 1; //例如1332 循环第一次变为1330-1=1329 第二次变为1300-1=1299
        }
        return res;
    }
};


int main() {
    Solution2 s;
    // int n = 10;
    // int n = 1234;
    // int n = 332;
    int n = 758458070;
    cout << s.monotoneIncreasingDigits(n);
    return 0;
}