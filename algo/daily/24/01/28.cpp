#include "../../head_file.h"

namespace std {
    int a = 10;
}

/*
problme: 

url: https://leetcode.cn/problems/freedom-trail/description/
 */
class Solution {
public:
    int findRotateSteps(string ring, string key) {
        vector<vector<int>> pos(26);
        for (int i = 0; i < ring.size(); ++i) {
            pos[ring[i] - 'a'].push_back(i);
        }
        // dp[i][j] 
        vector<vector<int>> dp(key.size(), vector<int>(ring.size(), INT_MAX));
        for (int i = 0; i < key.size(); ++i) {
            for (const auto &j : pos[key[i] - 'a']) {
                if (i == 0) {
                    // 没有前面的位置
                    dp[i][j] = min(dp[i][j], minDir(ring.size(), 0, j) + 1);
                } else {
                    // 前一个字符的位置
                    for (const auto &k : pos[key[i - 1] - 'a']) {
                        dp[i][j] = min(dp[i][j], dp[i - 1][k] + minDir(ring.size(), k, j) + 1);
                    }
                }
            }
        }
        return *min_element(dp.back().begin(), dp.back().end());
    }

private:
    int minDir(int len, int a, int b) {
        return min((len + a - b) % len, (len + b - a) % len);
    }
};

int main() {
    string ring = "godding";
    string key = "godding";
    cout << Solution().findRotateSteps(ring, key) << endl;
    return 0;
}