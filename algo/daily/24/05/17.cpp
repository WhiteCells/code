#include "../../head_file.h"

/*
problme: 

url: https://leetcode.cn/problems/most-profit-assigning-work/description/
 */

class Solution {
public:
    int maxProfitAssignment(vector<int>& difficulty, vector<int>& profit, vector<int>& worker) {
        vector<pair<int, int>> jobs;
        int n = profit.size(), res = 0, i = 0, best = 0;
        for (int j = 0; j < n; ++j) {
            jobs.emplace_back(difficulty[j], profit[j]);
        }
        sort(jobs.begin(), jobs.end());
        sort(worker.begin(), worker.end());
        for (int w : worker) {
            while (i < n && w >= jobs[i].first) {
                best = max(best, jobs[i].second);
                i++;
            }
            res += best;
        }
        return res;
    }
};

int main() {
    
    return 0;
}