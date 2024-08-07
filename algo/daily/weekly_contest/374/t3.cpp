#include "../../head_file.h"

/*
problme:

url:
 */

class Solution {
public:
    // igigee k=2
    // ee
    // igig
    // igigee

    // gvgvvgv k=2
    // vv
    int countCompleteSubstrings(string word, int k) {
        int n = word.size(), res = 0;
        for (int len = k; len <= n; len += k) {
            int i = 0, j = 0;
            int mp[26] = {};
            int cnt = 0; // 种类
            // 滑窗
            while (j < n) {
                while (j - i < len) {
                    cnt += mp[word[j] - 'a'] ? 0 : 1;
                    ++mp[word[j] - 'a'];
                    ++j;
                }
                int flag = true;
                for (int i = 0; i < 26; ++i) {
                    if (!(mp[i] == 0 || mp[i] == k)) {
                        flag = false;
                        break;
                    }
                }
                res += flag ? 1 : 0;
                --mp[word[i] - 'a'];
                cnt -= mp[word[i] - 'a'] == 0 ? 1 : 0;
                ++i;
            }
        }
        return res;
    }
};

int main() {
    // string word = "igigee";
    // int k = 2;
    string word = "gvgvvgv";
    int k = 2;
    cout << Solution().countCompleteSubstrings(word, k) << '\n';
    return 0;
}