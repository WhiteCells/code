#include "../../head_file.h"

/*
problme:

url:
 */

class Solution {
public:
    double mincostToHireWorkers(vector<int> &quality, vector<int> &wage, int k) {
        int n = quality.size();
        vector<int> h(n, 0);
        iota(h.begin(), h.end(), 0);
        sort(h.begin(), h.end(), [&](const int &a, const int &b) {
            return quality[a] * wage[b] > quality[b] * wage[a];
        });
        double res = 1e9;
        double totalq = 0.0;
        priority_queue<int, vector<int>, less<int>> q;
        for (int i = 0; i < k - 1; ++i) {
            totalq += quality[h[i]];
            q.push(quality[h[i]]);
        }
        for (int i = k - 1; i < n; ++i) {
            int idx = h[i];
            totalq += quality[idx];
            q.push(quality[idx]);
            double totalc = ((double)wage[idx] / quality[idx]) * totalq;
            res = min(res, totalc);
            totalq -= q.top();
            q.pop();
        }
        return res;
    }
};

int main() {
    vector<int> quality {10, 20, 5};
    vector<int> wage {70, 50, 30};
    std::cout << Solution().mincostToHireWorkers(quality, wage, 2) << std::endl;
    return 0;
}