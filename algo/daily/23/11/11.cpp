#include "../../head_file.h"

/*
problme:

url:
 */

// time complexity: O()
// spatial complexity: O()
class Solution {
public:
    int minSwapsCouples(vector<int> &row) {
        unordered_map<int, int> mp;
        int res = 0, n = row.size();
        for (int i = 0; i < n; i += 2) {
            mp[row[i]] = i;
            mp[row[i + 1]] = i + 1;
        }
        function<void(int)> dfs = [&](int i) -> void {
            if (i >= n) {
                return;
            }
            if (1 != abs(row[i] - row[i + 1]) || (min(row[i], row[i + 1]) & 1)) {
                int mate = row[i] & 1 ? row[i] - 1 : row[i] + 1;
                int index = mp[mate];
                mp[row[i + 1]] = index;
                mp[mate] = i + 1;
                swap(row[i + 1], row[index]);
                ++res;
            }
            dfs(i + 2);
        };
        dfs(0);
        return res;
    }
};

class Solution2 {
public:
    int minSwapsCouples(vector<int>& row) {
        unordered_map<int, int> mp;
        int n = row.size();
        for (int i = 0; i < n; i += 2) {
            mp[row[i]] = i;
            mp[row[i + 1]] = i + 1;
        }
        int res = 0;
        function<void(int)> dfs = [&](int i) -> void {
            if (i >= n) {
                return;
            }
            if (1 != abs(row[i] - row[i + 1]) || (min(row[i], row[i + 1])) & 1) {
                // row[i] 和 row[i + 1] 不匹配
                int mate = row[i] & 1 ? row[i] - 1 : row[i] + 1;
                int index = mp[mate];
                mp[mate] = i + 1;
                mp[row[i + 1]] = index;
                swap(row[i + 1], row[index]);
                ++res;
            }
            dfs(i + 2);
        };
        dfs(0);
        return res;
    }
};

int main() {
    std::vector<int> row { 0, 2, 4, 6, 7, 1, 3, 5 };
    cout << Solution().minSwapsCouples(row) << endl;
    return 0;
}