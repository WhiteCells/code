#include "../../head_file.h"

/*
problme:
示例 1：

输入：points = [[0,0],[1,0],[2,0]]
输出：2
解释：两个回旋镖为 [[1,0],[0,0],[2,0]] 和 [[1,0],[2,0],[0,0]]
示例 2：

输入：points = [[1,1],[2,2],[3,3]]
输出：2
示例 3：

输入：points = [[1,1]]
输出：0
url:
 */

class Solution {
public:
    int numberOfBoomerangs(vector<vector<int>> &points) {
        int res = 0;
        for (const auto &p : points) {
            unordered_map<int, int> mp;
            for (const auto &q : points) {
                ++mp[getDistance(p, q)];
            }
            // A(n, 2)
            for (const auto &[_, n] : mp) {
                res += n * (n - 1);
            }
        }
        return res;
    }
private:
    int getDistance(const vector<int> &p1, const vector<int> &p2) {
        // return sqrt(pow((p1[0] - p2[0]), 2) + pow(p1[1] - p2[1], 2));
        return pow((p1[0] - p2[0]), 2) + pow(p1[1] - p2[1], 2);
    }
};

int main() {
    vector<vector<int>> points {{1, 1}, {2, 2}, {3, 3}};
    // cout << Solution().numberOfBoomerangs(points) << endl;
    return 0;
}