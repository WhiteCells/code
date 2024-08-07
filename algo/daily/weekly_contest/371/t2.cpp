#include "../../head_file.h"

/*
problme:

url:
 */

// time complexity: O()
// spatial complexity: O()
class Solution {
public:
    vector<string> findHighAccessEmployees(vector<vector<string>> &access_times) {
        unordered_map<string, vector<string>> m;
        for (const auto &emp : access_times) {
            m[emp[0]].push_back(emp[1]);
        }
        vector<string> res;
        for (const auto &[name, time] : m) {
            if (time.size() < 3) {
                continue;
            }
            vector<string> tm = time;
            sort(tm.begin(), tm.end());
            int i = 0, j = 0;
            // 滑动窗口
            while (j < tm.size() - 1) {
                while (j - i + 1 < 3) {
                    ++j;
                }
                int dif = abs(stoi(tm[i]) - stoi(tm[j]));
                if (dif < 100) {
                    res.push_back(name);
                    break;
                }
                ++i;
            }
#if 1
            cout << name << " ";
            for (const auto &t : tm) {
                cout << t << " ";
            }
            cout << endl;
#endif
        }
        return res;
    }
};

int main() {
    // vector<vector<string>> access_times {
    //     { "a", "0549" },
    //     { "b", "0457" },
    //     { "a", "0532" },
    //     { "a", "0621" },
    //     { "b", "0540" }
    // };
    vector<vector<string>> access_times {
        { "akuhmu", "0454" },
        { "aywtqh", "0523" },
        { "akuhmu", "0518" },
        { "ihhkc", "0439" },
        { "ihhkc", "0508" },
        { "akuhmu", "0529" },
        { "aywtqh", "0530" },
        { "aywtqh", "0419" }
    };
    auto res = Solution().findHighAccessEmployees(access_times);
    for (const auto &name : res) {
        cout << name << endl;
    }
    return 0;
}