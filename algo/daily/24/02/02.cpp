#include "../../head_file.h"

/*
problme:

url: https://leetcode.cn/problems/stone-game-vi/
 */

class Solution {
public:
    int stoneGameVI(vector<int> &aliceValues, vector<int> &bobValues) {
        vector<tuple<int, int, int>> values;
        for (int i = 0; i < aliceValues.size(); ++i) {
            values.emplace_back(aliceValues[i] + bobValues[i],
                                aliceValues[i], bobValues[i]);
        }
        sort(values.begin(), values.end(), [](tuple<int, int, int> &a, tuple<int, int, int> &b) {
            return get<0>(a) > get<0>(b);
             });
        int sum1 = 0, sum2 = 0;
        for (int i = 0; i < aliceValues.size(); ++i) {
            if (i % 2) {
                sum2 += get<2>(values[i]);
            } else {
                sum1 += get<1>(values[i]);
            }
        }
        cout << sum1 << " " << sum2 << endl;
        if (sum1 > sum2) {
            return 1;
        } else if (sum1 < sum2) {
            return -1;
        } else {
            return 0;
        }
    }
};

int main() {
    vector<int> a {1, 3}, b {2, 1};
    cout << Solution().stoneGameVI(a, b) << endl;
    return 0;
}