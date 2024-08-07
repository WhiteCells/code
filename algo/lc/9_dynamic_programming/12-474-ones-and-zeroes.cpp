#include "../../head_file.h"

/*
 * @Author: Eorys
 * @Date: 2023-07-22 12:59:28
 * @Last Modified by: Eorys
 * @Last Modified time: 2023-07-22 12:59:28
 * @Description:
*/

class Solution {
public:
    int findMaxForm(vector<string>& strs, int m, int n) {
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        for (const auto& str : strs) {
            // 统计每一个字符串中的 0 和 1
            int one_cnt = 0, zero_cnt = 0;
            for (const auto& c : str) {
                if ('1' == c) {
                    ++one_cnt;
                }
                else {
                    ++zero_cnt;
                }
            }
            // 
            for (int i = m; i >= zero_cnt; --i) {
                for (int j = n; j >= one_cnt; --j) {
                    // 当前选择的 i个0 j个1 的子集是否是最大的
                    dp[i][j] = max(dp[i][j], dp[i - zero_cnt][j - one_cnt] + 1);
                }
            }
        }
        return dp[m][n];
    }
};


int main() {
    Solution s;

    // auto strs = vector<string>{ "10", "0001", "111001", "1", "0" };
    auto strs = vector<string>{ "10", "0", "1" };

    // int m = 5;
    int m = 1;

    // int n = 3;
    int n = 1;
    cout << s.findMaxForm(strs, m, n);
    return 0;
}