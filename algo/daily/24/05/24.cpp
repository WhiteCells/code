#include "../../head_file.h"

/*
problme: 

url: https://leetcode.cn/problems/find-the-most-competitive-subsequence/description/
 */

class Solution {
public:
    vector<int> mostCompetitive(vector<int>& nums, int k) {
        vector<int> st;
        for (int i = 0; i < nums.size(); ++i) {
            while (!st.empty() && nums[i] < st.back() && st.size() + nums.size() - i < k) {
                st.pop_back();
            }
            if (st.size() < k) {
                st.push_back(num[i]);
            }
        }
        return st;
    }
};

int main() {
    
    return 0;
}