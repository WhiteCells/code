#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int deleteGreatestValue(vector<vector<int>>& grid) {
        for (auto& g : grid) {
            sort(g.begin(), g.end());
        }
        int res = 0;
        for (int j = 0; j < grid[0].size(); ++j) {
            int mx = INT_MIN;
            for (int i = 0; i < grid.size(); ++i) {
                mx = max(mx, grid[i][j]);
            }
            res += mx;
        }
        return res;
    }
};


int main() {
    vector<vector<int>> grid{ { 1, 2, 4 }, { 3, 3, 1 } };
    Solution s;
    cout << s.deleteGreatestValue(grid);
    return 0;
}