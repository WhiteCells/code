#include "D:/distake/Coding/head_file.h"

/*
 * @Author: WhiteCells
 * @Date: 2023-06-15 16:35:50
 * @Last Modified by: WhiteCells
 * @Last Modified time: 2023-06-15 16:35:50
 * @Description: 1049. 最后一块石头的重量 II
 * https://leetcode.cn/problems/last-stone-weight-ii/
*/

class Solution {
public:
    int lastStoneWeightII(vector<int>& stones) {
        // 所有石头最多重 3000，只需要能放下一半
        vector<int> dp(15e3 + 1, 0);
        int sum = 0;
        for (int i = 0; i < stones.size(); ++i) {
            sum += stones[i];
        }
        int target = sum / 2;
        for (int i = 0; i < stones.size(); ++i) {
            for (int j = target; j >= stones[i]; --j) {
                dp[j] = max(dp[j], dp[j - stones[i]] + stones[i]);
            }
        }
        return sum - dp[target] - dp[target];
    }
};


int main() {
    Solution s;
    vector<int> stones{ 2, 7, 4, 1, 8, 1 };
    cout << s.lastStoneWeightII(stones);
    return 0;
}