#include "../../head_file.h"

/*
problme:

url: https://leetcode.cn/problems/defuse-the-bomb/description/
 */

class Solution {
public:
    vector<int> decrypt(vector<int> &code, int k) {
        int n = code.size();
        if (k == 0) {
            return vector<int>(n, 0);
        }
        vector<int> res;
        for (int i = 0; i < n; ++i) {
            int val = 0, j = i, cnt = abs(k);
            while (cnt--) {
                j = k > 0 ? j + n + 1 : j + n - 1;
                val += code[j % n];
            }
            res.push_back(val);
        }
        return res;
    }
};

int main() {
    vector<int> code {2,4,9,3};
    int k = -2;
    auto res = Solution().decrypt(code, k);
    for (auto ele : res) {
        cout << ele << " ";
    }
    return 0;
}