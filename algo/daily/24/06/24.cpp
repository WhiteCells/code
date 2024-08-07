#include "../../head_file.h"

/*
problme: 

url: https://leetcode.cn/problems/next-greater-element-ii/
 */

class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        int n = nums.size();
        vector<int> ans(n, -1);
        stack<int> st;
        for (int i = 2 * n - 1; i >= 0; i--) {
            int x = nums[i % n];
            while (!st.empty() && x >= st.top()) {
                st.pop();
            }
            if (i < n && !st.empty()) {
                ans[i] = st.top();
            }
            st.push(x);
        }
        return ans;
    }
};

int main() {
    
    return 0;
}