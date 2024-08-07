#include "D:/distake/Coding/head_file.h"

/*
 * @Author: WhiteCells
 * @Date: 2023-05-22 20:48:52
 * @Last Modified by: WhiteCells
 * @Last Modified time: 2023-05-22 20:48:52
 * @Description: 135.分发糖果
 * https://leetcode.cn/problems/candy/
*/

class Solution {
public:
    int candy(vector<int>& ratings) {
        vector<int> candyV(ratings.size(), 1);
        for (int i = 1; i < ratings.size(); ++i) { // 从第二个向右，和左边进行比较
            if (ratings[i] > ratings[i - 1]) {     // 当前评分大于左边的评分
                candyV[i] = candyV[i - 1] + 1;     // 当前糖果应该是左边已有的的糖果数加一
            }
        }
        for (int i = ratings.size() - 2; i >= 0; --i) {        // 从倒数第二个向左，和右边的进行比较
            if (ratings[i] > ratings[i + 1]) {                 // 当前评分大于右边的评分
                candyV[i] = max(candyV[i], candyV[i + 1] + 1); // 当前糖果数是右边已有的糖果数加一和当前已有的糖果数中的最大值
            }
        }
        int res = 0;
        for (int i = 0; i < candyV.size(); ++i) { // 统计总共需要的糖果数
            res += candyV[i];
        }
        return res;
    }
};


int main() {
    vector<int> ratings {1, 2, 2, 5, 4, 3, 2};
    Solution s;
    cout << s.candy(ratings);
    return 0;
}