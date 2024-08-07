#include "../../head_file.h"

/*
problme: 

url: https://leetcode.cn/problems/find-the-distinct-difference-array/
 */

class Solution {
public:
    vector<int> distinctDifferenceArray(vector<int>& nums) {
        int n = nums.size();
        vector<int> prev(n), suff(n);
        unordered_map<int, int> mp;
        for (int i = 0 ; i < n; ++i) {
            mp[nums[i]] = 1;
            prev[i] = mp.size();
        }
        mp.clear();
        for (int i = n - 1; i >= 0; --i) {
            suff[i] = mp.size();
            mp[nums[i]] = 1;
        }
        vector<int> res(n);
        for (int i = 0; i < n; ++i) {
            res[i] = prev[i] - suff[i];
        }
        return res;
    }
};

int main() {
    
    return 0;
}