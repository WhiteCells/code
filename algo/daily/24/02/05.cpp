#include "../../head_file.h"

/*
problme:

url: https://leetcode.cn/problems/jump-game-vi/description
 */

class Solution {
public:
    int maxResult(vector<int> &nums, int k) {
        int n = nums.size();
        vector<int> dp(n);
        dp[0] = nums[0];
        deque<int> queue;
        queue.push_back(0);
        for (int i = 1; i < n; i++) {
            while (!queue.empty() && queue.front() < i - k) {
                queue.pop_front();
            }
            dp[i] = dp[queue.front()] + nums[i];
            while (!queue.empty() && dp[queue.back()] <= dp[i]) {
                queue.pop_back();
            }
            queue.push_back(i);
        }
        return dp[n - 1];
    }
};

int main() {
    vector<int> nums {1, -1, -2, 4, -7, 3};
    cout << Solution().maxResult(nums, 2) << endl;
    return 0;
}