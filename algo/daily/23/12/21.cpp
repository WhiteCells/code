#include "../../head_file.h"

/*
problme: 

url: 
 */

class Solution {
public:
    long long maximumSumOfHeights(vector<int>& maxHeights) {
        int n = maxHeights.size();
        vector<long long> prefix(n), suffix(n);
        stack<int> st1;
        for (int i = 0; i < n; ++i) {
            while (!st1.empty() && maxHeights[i] < maxHeights[st1.top()]) {
                st1.pop();
            }
            if (st1.empty()) {
                prefix[i] = (long long)(i + 1) * maxHeights[i];
            } else {
                prefix[i] = prefix[st1.top()] + (long long)(i - st1.top()) * maxHeights[i];
            }
            st1.push(i);
        }
        long long res;
        stack<int> st2;
        for (int i = n - 1; i >= 0; --i) {
            while (!st2.empty() && maxHeights[i] < maxHeights[st2.top()]) {
                st2.pop();
            }
            if (st2.empty()) {
                suffix[i] = (long long)(n - i) * maxHeights[i];
            } else {
                suffix[i] = suffix[st2.top()] + (long long)(st2.top() - i) * maxHeights[i];
            }
            st2.push(i);
            // using each point as the highest point
            res = max(res, prefix[i] + suffix[i] - maxHeights[i]);
        }
        return res;
    }
};

int main() {
    vector<int> max_height {};
    cout << Solution().maximumSumOfHeights(max_height) << endl;
    return 0;
}