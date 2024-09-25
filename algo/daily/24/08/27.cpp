#include "../../head_file.h"

/*
problme:

url:
 */

class Solution {
public:
    int minimumSubstringsInPartition(string s) {
        int n = s.length();
        vector<int> memo(n);
        auto dfs = [&](auto&& dfs, int i) -> int {
            if (i < 0) {
                return 0;
            }
            int& res = memo[i]; // 注意这里是引用
            if (res) { // 之前计算过
                return res;
            }
            res = INT_MAX;
            int cnt[26]{}, k = 0, max_cnt = 0;
            for (int j = i; j >= 0; j--) {
                k += cnt[s[j] - 'a']++ == 0;
                max_cnt = max(max_cnt, cnt[s[j] - 'a']);
                if (i - j + 1 == k * max_cnt) {
                    res = min(res, dfs(dfs, j - 1) + 1);
                }
            }
            return res;
        };
        return dfs(dfs, n - 1);
    }
};

int main()
{
    Solution().minimumSubstringsInPartition("fabccddg");

    return 0;
}