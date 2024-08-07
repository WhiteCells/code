#include <iostream>

using namespace std;
// https://leetcode.cn/problems/subtract-the-product-and-sum-of-digits-of-an-integer/

class Solution {
public:
    int subtractProductAndSum(int n) {
        int digit_multi = 1, digit_sum = 0;
        while (n) {
            int digit = n % 10;
            digit_multi *= digit;
            digit_sum += digit;
            n /= 10;
        }
        return digit_multi - digit_sum;
    }
};


int main() {
    Solution s;
    cout << s.subtractProductAndSum(234);
    return 0;
}