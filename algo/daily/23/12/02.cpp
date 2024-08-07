#include "../../head_file.h"

/*
problme:

url:
 */

class Solution {
public:
    bool carPooling(vector<vector<int>> &trips, int capacity) {
        int mx = 0;
        for (const auto &t : trips) {
            mx = max(mx, t[2]);
        }
        vector<int> diff(mx + 1);
        for (const auto &t : trips) {
            diff[t[1]] += t[0];
            diff[t[2]] -= t[0];
        }
        int cur = 0;
        for (int i = 0; i <= mx; ++i) {
            cur += diff[i];
            if (cur > capacity) {
                return false;
            }
        }
        return true;
    }
};

class Solution {
public:
    bool carPooling(vector<vector<int>> &trips, int capacity) {
        vector<int> site(1001);
        for (const auto &t : trips) {
            int p = t[0], s = t[1], e = t[2];
            for (int i = s; i < e; ++i) {
                site[i] += p;
                if (site[i] > capacity) {
                    return false;
                }
            }
        }
        return true;
    }
};

int main() {
    vector<vector<int>> trips {
        // {3, 2, 9},
        // {2, 1, 7},

        {3, 2, 7},
        {3, 7, 9},
        {8, 3, 9},
    };
    int capacity = 11;
    cout << Solution().carPooling(trips, capacity) << '\n';
    return 0;
}