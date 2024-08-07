#include "../../head_file.h"

/*
problme:
输入：maxHeights = [5,3,4,1,1]
输出：13
解释：和最大的美丽塔方案为 heights = [5,3,3,1,1] ，这是一个美丽塔方案，因为：
- 1 <= heights[i] <= maxHeights[i]
- heights 是个山脉数组，峰值在 i = 0 处。
13 是所有美丽塔方案中的最大高度和。
url: https://leetcode.cn/problems/beautiful-towers-i/description/
 */

class Solution {
public:
    long long maximumSumOfHeights(vector<int> &h) {
        long long res = 0;
        for (int mid = 0; mid < h.size(); ++mid) {
            long long sum = 0;
            int m = h[mid];
            for (int left = mid - 1; left >= 0; --left) {
                m = min(m, h[left]);
                sum += min(h[left], m);
            }
            m = h[mid];
            for (int right = mid; right < h.size(); ++right) {
                m = min(m, h[right]);
                sum += min(h[right], m);
            }
            res = max(res, sum);
        }
        return res;
    }
};

int main() {
    // vector<int> maxHeights {5, 3, 4, 1, 1}; // 13
    vector<int> maxHeights {6, 5, 3, 9, 2, 7}; // 22
    cout << Solution().maximumSumOfHeights(maxHeights) << endl;
    return 0;
}