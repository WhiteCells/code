#include "../../head_file.h"

/*
problme: 

url: https://leetcode.cn/problems/count-of-integers/
 */

// TODO
class Solution {
    const int MOD = 1'000'000'007;

    int calc(string &s, int min_sum, int max_sum) {
        int n = s.length();
        vector<vector<int>> memo(n, vector<int>(min(9 * n, max_sum) + 1, -1));
        function<int(int, int, bool)> dfs = [&](int i, int sum, bool is_limit) -> int {
            if (sum > max_sum) { // 非法
                return 0;
            }
            if (i == n) {
                return sum >= min_sum ? 1 : 0;
            }
            if (!is_limit && memo[i][sum] != -1) {
                return memo[i][sum];
            }

            int up = is_limit ? s[i] - '0' : 9;
            int res = 0;
            for (int d = 0; d <= up; d++) { // 枚举当前数位填 d
                res = (res + dfs(i + 1, sum + d, is_limit && d == up)) % MOD;
            }

            if (!is_limit) {
                memo[i][sum] = res;
            }
            return res;
        };
        return dfs(0, 0, true);
    }

public:
    int count(string num1, string num2, int min_sum, int max_sum) {
        int ans = calc(num2, min_sum, max_sum) - calc(num1, min_sum, max_sum) + MOD; // 避免负数
        int sum = 0;
        for (char c : num1) {
            sum += c - '0';
        }
        ans += min_sum <= sum && sum <= max_sum; // num1 是合法的，补回来
        return ans % MOD;
    }
};
int main() {
    int a = 1000'000'000;
    cout << a << endl;
    return 0;
}