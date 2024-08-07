#include "../../head_file.h"

/*
problme: 

url: https://leetcode.cn/problems/number-of-beautiful-pairs
 */

class Solution {
public:
    int countBeautifulPairs(vector<int>& nums) {
        int res = 0, n = nums.size();
        for (int i = 0; i < n; ++i) {
            int one = nums[i];
            while (one >= 10) {
                one /= 10;
            }
            for (int j = i + 1; j < n; ++j) {
                if (gcd(one, nums[j] % 10) == 1) {
                    ++res;
                }
            }
        }
        return res;
    }
};

int main() {
    
    return 0;
}