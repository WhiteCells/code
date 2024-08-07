#include "../../head_file.h"

/*
problme: 

url: 
 */

class Solution {
public:
    int maxScore(vector<int> &cardPoints, int k) {
        int n = cardPoints.size() - k;
        int i = 0, j = 0;
        int mn = INT_MAX; // 滑窗最小值
        int cur = 0;
        while (j < cardPoints.size()) {
            while (j - i < n) {
                cur += cardPoints[j];
                ++j;
            }
            mn = min(mn, cur);
            cur -= cardPoints[i];
            ++i;
        }
        return accumulate(cardPoints.begin(), cardPoints.end(), 0) - mn;
    }
};

int main() {
    vector<int> cardPoints {1,2,3,4,5,6,1};
    int k = 3;
    cout << Solution().maxScore(cardPoints, k) << '\n';
    return 0;
}