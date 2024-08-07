#include "../../head_file.h"

/*
problme:

url:
 */

class Solution {
public:
    int maxSatisfied(vector<int> &customers, vector<int> &grumpy, int minutes) {
        int i = 0, j = minutes, n = customers.size(), res = 0;
        for (int k = 0; k < n; ++k) {
            res += grumpy[k] ? 0 : customers[k];
        }
        int back = res;
        while (j <= n) {
            int cur = back;
            for (int m = i; m < j; ++m) {
                if (grumpy[m]) {
                    cur += customers[m];
                }
            }
            if (cur > res) {
                res = cur;
            }
            ++i;
            ++j;
        }
        return res;
    }
};

int main() {
    vector<int> customers {1,0,1,2,1,1,7,5};
    vector<int> grumpy    {0,1,0,1,0,1,0,1};
    int minutes = 3;

    std::cout << Solution().maxSatisfied(customers, grumpy, minutes) << std::endl;

    return 0;
}