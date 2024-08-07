#include "../../head_file.h"

/*
problme:
输入：s = "leetscode", dictionary = ["leet","code","leetcode"]
输出：1
解释：将 s 分成两个子字符串：下标从 0 到 3 的 "leet" 和下标从 5 到 8 的 "code" 。
只有 1 个字符没有使用（下标为 4），所以我们返回 1 。
url: https://leetcode.cn/problems/extra-characters-in-a-string/description/
 */

// TODO
class Solution {
public:
    int minExtraChar(string s, vector<string> &dictionary) {
        // 优先从最长的开始匹配
        sort(dictionary.begin(), dictionary.end());
        for (const auto &str : dictionary) {
            // KMP

        }
        return isMatch("abcleet", "leet");
    }
private:
    // 返回匹配下标，不匹配返回 -1
    int isMatch(string s, string sub) {
        if (sub.size() > s.size()) {
            return -1;
        }
        int i = 0;
        while (i <= s.size() - sub.size()) {
            int j = 0, tmp = i;
            while (s[i] == sub[j]) {
                ++i;
                ++j;
                if (i - tmp + 1 == sub.size()) {
                    return tmp;
                }
            }
            i = tmp + 1;
        }
        return -1;
    }
};

class Solution2 {
public:
    int minExtraChar(string s, vector<string>& dictionary) {
        int n = s.size();
        vector<int> d(n + 1, INT_MAX);
        unordered_map<string, int> mp;
        for (auto s : dictionary) {
            mp[s]++;
        }
        d[0] = 0;
        for (int i = 1; i <= n; i++) {
            d[i] = d[i - 1] + 1;
            for (int j = i - 1; j >= 0; j--) {
                if (mp.count(s.substr(j, i - j))) {
                    d[i] = min(d[i], d[j]);
                }
            }
        }
        return d[n];
    }
};

int main() {
    vector<string> dictionary {""};
    cout << Solution().minExtraChar(string(), dictionary) << endl;
    return 0;
}