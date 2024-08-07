#include "../../head_file.h"

/*
problme:

url:
 */

// time complexity: O()
// spatial complexity: O()
class Solution {
public:
    int findTheCity(int n, vector<vector<int>> &edges, int distanceThreshold) {
        vector<vector<int>> mp(n, vector<int>(n, (int)1e9));
        for (const auto &edge : edges) {
            mp[edge[0]][edge[1]] = edge[2];
            mp[edge[1]][edge[0]] = edge[2];
        }
        for (int k = 0; k < n; ++k) {
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    if (i != j && i != k && j != k && mp[i][j] > mp[i][k] + mp[k][j]) {
                        mp[i][j] = mp[i][k] + mp[k][j];
                    }
                }
            }
        }
        int res = -1, mn = INT_MAX;
        for (int i = 0; i < n; ++i) {
            int cnt = 0;
            for (int j = 0; j < n; ++j) {
                if (i != j && distanceThreshold >= mp[i][j]) {
                    ++cnt;
                }
            }
            if (cnt <= mn) {
                res = i;
                mn = cnt;
            }
        }
        return res;
    }
};

int main() {
    vector<vector<int>> edges {
        { 0, 1, 3 },
        { 1, 2, 1 },
        { 1, 3, 4 },
        { 2, 3, 1 }
    };
    int distanceThreshold = 4;
    cout << Solution().findTheCity(4, edges, distanceThreshold) << '\n';
    return 0;
}