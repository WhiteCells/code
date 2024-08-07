#include "../../head_file.h"

/*
problme: 
寻找某一个数字 xxx，当我们将豆子数量小于 xxx 的袋子清空，
并将豆子数量大于 xxx 的袋中豆子数量变为 xxx 时，拿出的豆子数量最少。
url: https://leetcode.cn/problems/removing-minimum-number-of-magic-beans
 */

class Solution {
public:
    long long minimumRemoval(vector<int>& beans) {
        sort(beans.begin(), beans.end());
        long long total = accumulate(beans.begin(), beans.end(), 0LL), res = total;
        for (int i = 0; i < beans.size(); ++i) {
            res = min(res, total - (long long)(beans[i] * (beans.size() - i)));
        }
        return res;
    }
};

int main() {
    vector<int> beans {4, 1, 6, 5};
    cout << Solution().minimumRemoval(beans) << endl;
    return 0;
}