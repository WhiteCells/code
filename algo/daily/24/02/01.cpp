#include "../../head_file.h"

/*
problme: 

url: 
 */

class Solution {
public:
    vector<int> numsGame(vector<int> &nums) {
        int n = nums.size();
        vector<int> res(n);
        priority_queue<int> lower;
        priority_queue<int, vector<int>, greater<>> upper;
        long long mod = 1e9 + 7;
        long long lowerSum = 0, upperSum = 0;
        for (int i = 0; i < n; i++) {
            int x = nums[i] - i;
            if (lower.empty() || lower.top() >= x) {
                lowerSum += x;
                lower.push(x);
                if (lower.size() > upper.size() + 1) {
                    upperSum += lower.top();
                    upper.push(lower.top());
                    lowerSum -= lower.top();
                    lower.pop();
                }
            } else {
                upperSum += x;
                upper.push(x);
                if (lower.size() < upper.size()) {
                    lowerSum += upper.top();
                    lower.push(upper.top());
                    upperSum -= upper.top();
                    upper.pop();
                }
            }
            if ((i + 1) % 2 == 0) {
                res[i] = (upperSum - lowerSum) % mod;
            } else {
                res[i] = (upperSum - lowerSum + lower.top()) % mod;
            }
        }
        return res;
    }
};

int main() {
    
    return 0;
}