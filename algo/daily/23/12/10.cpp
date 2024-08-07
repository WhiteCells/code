#include "../../head_file.h"

/*
problme:

url:
 */

class Solution {
public:
    int climbStairs(int n) {
        if (1 == n) {
            return 1;
        } else if (2 == n) {
            return 2;
        }
        int a = 1, b = 2, c = 3;
        for (int i = 3; i < n; ++i) {
            a = b;
            b = c;
            c = a + b;
        }
        return c;
    }
};

class Solution2 {
public:
    int climbStairs(int n) {
        vector<int> memo(n + 1, -1);
        function<int(int)> dfs = [&](int i) -> int {
            if (-1 != memo[i]) {
                return memo[i];
            }
            if (1 == i) {
                return 1;
            } else if (2 == i) {
                return 2;
            }
            return memo[i] = dfs(i - 1) + dfs(i - 2);
        };
        return dfs(n);
    }
};

int main() {
    cout << Solution().climbStairs(5) << endl;
    cout << Solution2().climbStairs(5) << endl;
    return 0;
}