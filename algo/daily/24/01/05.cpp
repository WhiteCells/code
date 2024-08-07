#include "../../head_file.h"

/*
problme:

url: https://leetcode.cn/problems/number-of-visible-people-in-a-queue/description/
 */

// 单调栈
class Solution {
public:
    vector<int> canSeePersonsCount(vector<int> &heights) {
        stack<int> st;
        int n = heights.size();
        vector<int> res(n, 0);
        for (int i = n - 1; i >= 0; --i) {
            while (!st.empty() && heights[i] > st.top()) {
                st.pop();
                res[i] += 1;
            }
            // 除了最右侧一个人外至少，每个人都能至少看到右侧一个人
            if (!st.empty()) {
                res[i] += 1;
            }
            st.push(heights[i]);
        }
        return res;
    }
};

int main() {
    vector<int> heights {10, 6, 8, 5, 11, 9};
    auto res = Solution().canSeePersonsCount(heights);
    for (const auto &ele : res) {
        cout << ele << ' ';
    }
    cout << endl;
    return 0;
}