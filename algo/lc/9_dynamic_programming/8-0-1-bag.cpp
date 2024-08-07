#include "D:/distake/Coding/head_file.h"

/*
 * @Author: WhiteCells
 * @Date: 2023-06-09 11:20:18
 * @Last Modified by: WhiteCells
 * @Last Modified time: 2023-06-09 11:20:18
 * @Description:
*/


// 二维数组
class Solution1 {
public:
    int twoDimension01Bag(int w, vector<int> weight, vector<int> value) {
        vector<vector<int>> dp(weight.size(), vector<int>(w + 1, 0));
        for (int j = weight[0]; j <= w; ++j) { // 从重量最小的物品下标开始初始化 dp
            dp[0][j] = value[0];
        }
        for (int i = 1; i < weight.size(); ++i) {
            for (int j = 1; j <= w; ++j) {
                if (weight[i] > j) { // 当前物品重量大于背包容量，不能放进背包
                    dp[i][j] = dp[i - 1][j]; // 上一个物品放到 j 里就是背包价值总和最大
                }
                else { // 当前物品可以放进背包
                    dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - weight[i]] + value[i]);
                }
            }
        }
        return dp[weight.size() - 1][w];
    }
};

// 一维数组
class Solution2 {
public:
    int oneDimension01Bag(int w, vector<int> weight, vector<int> value) {
        vector<int> dp(w + 1, 0);
        for (int i = 0; i < weight.size(); ++i) {
            for (int j = w; j >= weight[i]; --j) {
                dp[j] = max(dp[j], dp[j - weight[i]] + value[i]);
            }
        }
        return dp[w];
    }
};


int main() {
    Solution1 s1;
    Solution2 s2;
    int w = 4; // 背包容量
    vector<int> weight {1, 3, 4};
    vector<int> value {15, 20, 30};
    cout << s1.twoDimension01Bag(w, weight, value) << '\n';
    cout << s2.oneDimension01Bag(w, weight, value) << '\n';
    return 0;
}


//  	  重量   价值
// 物品0 	1 	  15
// 物品1 	3 	  20
// 物品2 	4 	  30

// class Solution {
// public:
//     int Solve(vector<vector<int>>& nums) {
//     }
// };