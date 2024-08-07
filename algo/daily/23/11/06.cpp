#include "../../head_file.h"

/*
problme:

url:
 */

// time complexity: O()
// spatial complexity: O()
class Solution1 {
public:
    int maxProduct(vector<string> &words) {
        int res = 0, n = words.size();
        for (int i = 0; i + 1 < n; ++i) {
            int arr[26] = { 0 };
            for (const auto &c : words[i]) {
                ++arr[c - 'a'];
            }
            for (int j = i + 1; j < n; ++j) {
                bool flag = false;
                for (const auto &c : words[j]) {
                    if (arr[c - 'a']) {
                        flag = true;
                        break;
                    }
                }
                if (!flag) {
                    res = max(res, (int)(words[i].size() * words[j].size()));
                }
            }
        }
        return res;
    }
};


class Solution2 {
public:
    int maxProduct(vector<string> &words) {
        int res = 0, n = words.size();
        vector<int> v(n); // 存放每一个字符串的掩码
        for (int i = 0; i < n; ++i) {
            for (const auto &c : words[i]) {
                v[i] |= 1 << (c - 'a');
            }
        }
        for (int i = 0; i + 1 < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (!(v[i] & v[j])) {
                    res = max(res, (int)(words[i].size() * words[j].size()));
                }
            }
        }
        return res;
    }
};

class Solution3 {
public:
    int maxProduct(vector<string> &words) {
        int res = 0, n = words.size();
        vector<int> v(n);
        unordered_map<int, int> mp;
        for (int i = 0; i < n; ++i) {
            for (const auto &c : words[i]) {
                v[i] |= 1 << (c - 'a');
            }
            if (mp.count(v[i])) {
                mp[v[i]] = max(mp[v[i]], (int)words[i].size());
            } else {
                mp[v[i]] = words[i].size();
            }
        }
        for (int i = 0; i + 1 < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (!(v[i] & v[j])) {
                    res = max(res, mp[v[i]] * mp[v[j]]);
                }
            }
        }
        return res;
    }
};

int main() {
    // vector<string> words { "abcw", "baz", "foo", "bar", "xtfn", "abcdef" };
    vector<string> words { "eae", "ea", "aaf", "bda", "fcf", "dc", "ac", "ce", "cefde", "dabae" }; // 15
    cout << Solution1().maxProduct(words) << endl;
    cout << Solution2().maxProduct(words) << endl;
    cout << Solution3().maxProduct(words) << endl;
    return 0;
}