#include "../../head_file.h"

/*
problme: 

url: https://leetcode.cn/problems/minimum-rounds-to-complete-all-tasks/
 */

class Solution {
public:
    int minimumRounds(vector<int>& tasks) {
        unordered_map<int, int> mp;
        for (const auto &task : tasks) {
            ++mp[task];
        }
        int res = 0;
        for (const auto &[_, cnt] : mp) {
            if (cnt == 1) {
                return -1;
            } else if (cnt % 3) {
                res += cnt / 3 + 1;
            } else {
                res += cnt / 3;
            }
        }
        return res;
    }
};

int main() {
    
    return 0;
}