#include <iostream>
#include <set>
#include <vector>

using namespace std;
// https://leetcode.cn/problems/card-flipping-game/submissions/

class Solution {
public:
    int flipgame(vector<int>& fronts, vector<int>& backs) {
        multiset<int> s;
        int res = INT_MAX;
        int n = fronts.size();
        for (int i = 0; i < n; ++i) {
            if (fronts[i] == backs[i]) {
                s.insert(fronts[i]);
            }
        }
        for (int i = 0; i < fronts.size(); ++i) {
            int front = fronts[i], back = backs[i];
            if (!s.count(front)) {
                res = min(res, front);
            }
            if (!s.count(back)) {
                res = min(res, back);
            }
        }
        return INT_MAX == res ? 0 : res;
    }
};

int main() {
    // auto fronts = vector<int>{ 1, 2, 4, 4, 7 }, backs = vector<int>{ 1, 3, 4, 1, 3 };
    auto fronts = vector<int>{ 1, 1 }, backs = vector<int>{ 2, 1 };
    Solution s;
    cout << s.flipgame(fronts, backs);
    return 0;
}