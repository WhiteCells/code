#include "../../head_file.h"

/*
problme:

url:
 */

class Solution {
public:
    int minCostClimbingStairs(vector<int> &cost) {
        int n = cost.size();
        vector<int> res(n + 1, 0);
        for (int i = 3; i <= n; ++i) {
            res[i] = min(res[i - 1] + cost[i - 1], res[i - 2] + cost[i - 2]);
        }
        return res[n];
    }
};

int main() {
    vector<int> cost {10, 15, 20};
    cout << Solution().minCostClimbingStairs(cost) << endl;
    return 0;
}