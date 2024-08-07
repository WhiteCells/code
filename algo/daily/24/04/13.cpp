#include "../../head_file.h"

/*
problme: 

url: 
 */

class Solution {
public:
    int findChampion(int n, vector<vector<int>>& edges) {
        vector<int> in_cnt(n);
        for (const auto &edge : edges) {
            ++in_cnt[edge[1]];
        }
        int cnt = 0, res = 0;
        for (size_t i = 0; i < in_cnt.size(); ++i) {
            if (!in_cnt[i]) {
                ++cnt;
                res = i;
            }
        }
        return cnt == 1 ? res : -1;
    }
};

int main() {
    vector<vector<int>> edge {{0, 1}, {1, 2}};
    int n = 3;
    std::cout << Solution().findChampion(n, edge) << std::endl;
    return 0;
}