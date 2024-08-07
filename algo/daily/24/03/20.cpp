#include "../../head_file.h"

/*
problme:

url: https://leetcode.cn/problems/minimum-non-zero-product-of-the-array-elements/
 */

class Solution {
public:
    int minNonZeroProduct(int p) {
        if (p == 1) {
            return 1;
        }
        const long long mod = 1e9 + 7;
        auto fastPow = [=](long long x, long long n) {
            long long res = 1;
            while (n > 0) {
                if (n & 1) {
                    res = res * x % mod;
                }
                x = x * x % mod;
                n >>= 1;
            }
            return res;
            };
        long long x = fastPow(2, p) - 1;
        long long y = 1LL << (p - 1);
        return fastPow(x - 1, y - 1) * x % mod;
    }
};

int main() {
    return 0;
}