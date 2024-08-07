#include "../../head_file.h"

/*
problme: 

url: 
 */

class Solution {
public:
    int minimumSeconds(vector<int>& nums) {
        unordered_map<int, vector<int>> mp;
        int n = nums.size();
        for (int i = 0; i < n; ++i) {
            mp[nums[i]].push_back(i);
        }
        int res = n;
        for (const auto &[_, v] : mp) {
            int mx = v.front() + n - v.back();
            for (int i = 1; i < (int)v.size(); ++i) {
                mx = max(mx, v[i] - v[i - 1]);
            }
            res = min(res, mx / 2);
        }
        return res;
    }
};

int main() {
    vector<int> nums {2, 1, 3, 3, 2};
    cout << Solution().minimumSeconds(nums) << endl;
    return 0;
}