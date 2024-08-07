#include "../../head_file.h"

/*
problme:

url:
 */

class Solution {
public:
    long long totalCost(vector<int> &costs, int k, int candidates) {
        int n = costs.size();

        // 前 candidates 与后 candidates 相加大于 costs 数组的大小
        // 则说明只需要 costs 中前 k 个最小的员工代价即可
        if (candidates * 2 >= n) {
            sort(costs.begin(), costs.end());
            return accumulate(costs.begin(), costs.begin() + k, 0LL);
        }

        using PII = pair<int, int>;
        auto cmp = [&](const PII &p1, const PII &p2) {
            return p1.first == p2.first ?
                p1.second > p2.second : p1.first > p2.first;
        };
        priority_queue<PII, vector<PII>, decltype(cmp)> heap(cmp);
        // priority_queue<PII, vector<PII>, greater<PII>> heap;

        // 两个区间，前 condidates 与后 condidates
        // left1, ..., right1, ..., left2, ..., right2
        int left1 = 0, right1 = candidates;
        int left2 = n - candidates, right2 = n;
        for (int i = left1; i < right1; ++i) {
            heap.push({costs[i], i});
        }
        for (int i = left2; i < right2; ++i) {
            heap.push({costs[i], i});
        }

        long long res = 0;
        while (k--) {
            auto t = heap.top();
            heap.pop();
            res += t.first;

            // 两个区间存在覆盖
            if (right1 + 1 >= left2) {
                continue;
            }

            if (t.second <= right1) {
                ++right1;
                heap.push({costs[right1], right1});
            } else {
                --left2;
                heap.push({costs[left2], left2});
            }
        }
        return res;
    }
};

int main() {
    vector<int> costs {17,12,10,2,7,2,11,20,8};
    cout << Solution().totalCost(costs, 3, 4) << std::endl;
    return 0;
}