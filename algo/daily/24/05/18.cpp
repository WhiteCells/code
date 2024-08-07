#include "../../head_file.h"

/*
problme:

url: 
 */

class Solution {
public:
    int maxDivScore(vector<int>& nums, vector<int>& divisors) {
        int res = INT_MAX, cnt = 0;
        for (const auto &divisor : divisors) {
            int cur = 0;
            for (const auto &num : nums) {
                cur += (num % divisor == 0);
            }
            if (cur == cnt) {
                res = min(res, divisor);
            } else if (cur > cnt) {
                res = divisor;
                cnt = cur;
            }
        }
        return res;
    }
};

int main() {
    vector<int> nums {73,13,20,6};
    vector<int> divisors {56,75,83,26,24,53,56,61};
    cout << Solution().maxDivScore(nums, divisors) << endl;
    return 0;
}