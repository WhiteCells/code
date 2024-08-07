#include "../../head_file.h"

/*
problme:

url: https://leetcode.cn/problems/maximum-number-of-operations-with-the-same-score-ii/
 */

class Solution {
public:
    int maxOperations(vector<int> &nums) {
        int n = nums.size();
        int res1 = maxOperationsOfIntervals(2, n - 1, nums[0] + nums[1], nums);
        int res2 = maxOperationsOfIntervals(1, n - 2, nums[0] + nums[n - 1], nums);
        int res3 = maxOperationsOfIntervals(0, n - 3, nums[n - 2] + nums[n - 1], nums);
        return max({res1, res2, res3}) + 1;
    }

private:
    vector<vector<int>> memo;

    /// @param i 左区间
    /// @param j 右区间
    /// @param score 相同分数
    /// @param nums 区间内的值
    /// @return 区间的最大操作数
    int maxOperationsOfIntervals(int i, int j, int score, vector<int> &nums) {
        memo.assign(nums.size(), vector<int>(nums.size(), -1));

        function<int(int, int, int)> dfs = [&](int i, int j, int score) -> int {
            if (i >= j) {
                return 0;
            }
            int &res = memo[i][j];
            if (res != -1) {
                return memo[i][j];
            }
            res = 0;
            if (nums[i] + nums[i + 1] == score) {
                res = max(res, dfs(i + 2, j, score) + 1);
            }
            if (nums[i] + nums[j] == score) {
                res = max(res, dfs(i + 1, j - 1, score) + 1);
            }
            if (nums[j - 1] + nums[j] == score) {
                res = max(res, dfs(i, j - 2, score) + 1);
            }
            return res;
        };
        return dfs(i, j, score);
    }
};

class Solution2 {
public:
    int maxOperations(vector<int> &nums) {
        int n = nums.size();
        vector<vector<int>> memo(n, vector<int>(n));

        /// @param i 左区间
        /// @param j 右区间
        /// @param return 区间最大可操作数
        auto helper = [&](int i, int j, int score) {
            for (auto &row : memo) {
                fill(row.begin(), row.end(), -1);
            }

            function<int(int, int)> dfs = [&](int i, int j) -> int {
                if (i >= j) {
                    return 0;
                }
                if (memo[i][j] != -1) {
                    return memo[i][j];
                }
                memo[i][j] = 0;
                if (nums[i] + nums[i + 1] == score) {
                    memo[i][j] = max(memo[i][j], dfs(i + 2, j) + 1);
                }
                if (nums[i] + nums[j] == score) {
                    memo[i][j] = max(memo[i][j], dfs(i + 1, j - 1) + 1);
                }
                if (nums[j - 1] + nums[j] == score) {
                    memo[i][j] = max(memo[i][j], dfs(i, j - 2) + 1);
                }
                return memo[i][j];
            };

            return dfs(i, j);
        };

        int res1 = helper(0, n - 3, nums[n - 2] + nums[n - 1]);
        int res2 = helper(1, n - 2, nums[0] + nums[n - 1]);
        int res3 = helper(2, n - 1, nums[0] + nums[1]);

        return max({res1, res2, res3}) + 1;
    }
};

int main() {
    vector<int> nums {3, 1, 9, 3, 6, 6, 3, 2, 4};
    cout << Solution2().maxOperations(nums) << endl;
    return 0;
}