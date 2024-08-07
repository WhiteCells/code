#include "../../head_file.h"

/*
problme:

url:
 */

class Solution {
public:
    int countPaths(int n, vector<vector<int>> &roads) {
        vector<vector<long long>> dis(n, vector<long long>(n, LLONG_MAX / 2));
        vector<vector<long long>> dp(n, vector<long long>(n));

        for (int i = 0; i < n; ++i) {
            dis[i][i] = 0;
            dp[i][i] = 1;
        }

        for (const auto &r : roads) {
            dis[r[0]][r[1]] = r[2];
            dis[r[1]][r[0]] = r[2];
            dp[r[0]][r[1]] = 1;
            dp[r[1]][r[0]] = 1;
        }

        static constexpr int mod = 1e9 + 7;
        for (int k = 0; k < n; ++k) {
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    if (k != i && k != j && i != j) {
                        long long sum = dis[i][k] + dis[k][j];
                        if (sum < dis[i][j]) {
                            dis[i][j] = sum;
                            dp[i][j] = dp[i][k] * dp[k][j];
                            dp[i][j] %= mod;
                        } else if (sum == dis[i][j]) {
                            dp[i][j] += dp[i][k] * dp[k][j];
                            dp[i][j] %= mod;
                        }
                    }
                }
            }
        }

        return dp[0][n - 1];
    }
};

int main() {

    return 0;
}