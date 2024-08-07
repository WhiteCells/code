#include "../../head_file.h"

/*
problme: 

url: https://leetcode.cn/problems/find-players-with-zero-or-one-losses/
 */

class Solution {
public:
    vector<vector<int>> findWinners(vector<vector<int>>& matches) {
        vector<vector<int>> res(2, vector<int>());
        map<int, int> cnt;
        for (const auto matche : matches) {
            ++cnt[matche[1]];
            if (!cnt.count(matche[0])) {
                cnt[matche[0]] = 0;
            }
        }
        for (const auto &p : cnt) {
            if (p.second == 0) {
                res[0].push_back(p.first);
            } else if (p.second == 1) {
                res[1].push_back(p.first);
            }
        }
        return res;
    }
};

int main() {
    
    return 0;
}