#include <iostream>

using namespace std;

class Solution {
public:
    int alternateDigitSum(int n) {
        int arr[10], i = 0, sum = 0;
        for (int i = 0; i < 10; ++i) {
            arr[i] = -1;
        }
        while (n) {
            arr[i++] = n % 10;
            n /= 10;
        }
        for (int i = 9; i >= 0; --i) {
            if (arr[i] == -1) {
                continue;
            }
            else {
                int j = 0;
                while (i >= 0) {
                    if (j % 2 == 0) {
                        sum += arr[i];
                    }
                    else {
                        sum -= arr[i];
                    }
                    ++j;
                    --i;
                }
                break;
            }
        }
        return sum;
    }
};

class Solution2 {
public:
    int alternateDigitSum(int n) {
        int sum = 0, sign = 1;
        // 1 -2 5 和 -1 2 -5 互为相反数
        // n 有奇数位，最低位是正，结果返回 sum
        // n 有偶数位，最低位是负，结果返回 -sum
        while (n) {
            sum += sign * (n % 10); // 默认以最低位为正（n 有奇数位的情况）
            sign = -sign;
            n /= 10;
        }
        // 奇数位 sign == -1，偶数位 sign == 1
        return -sign * sum;
    }
};

int main() {
    // int n = 521;
    int n = 886997;
    Solution2 s;
    cout << s.alternateDigitSum(n);
    return 0;
}