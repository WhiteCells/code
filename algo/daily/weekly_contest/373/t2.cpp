#include "../../head_file.h"

/*
problme: 

url: https://leetcode.cn/problems/count-beautiful-substrings-i/
 */
// TLE
class Solution {
public:
    int beautifulSubstrings(string s, int k) {
        int res = 0;
        for (int i = 0; i < s.size(); ++i) {
            for (int j = 1; j <= s.size() - i; ++j) {
                string sub = s.substr(i, j);
                int vowels = 0;
                for (const auto &c : sub) {
                    if ('a' == c || 'e' == c || 'i' == c || 'o' == c || 'u' == c) {
                        ++vowels;
                    }
                }
                int consonants = sub.size() - vowels;
                if (vowels == consonants && 0 == (vowels * consonants) % k) {
                    ++res;
                }
            }
        }
        return res;
    }
};

// time complexity: O()
// spatial complexity: O()
class Solution2 {
public:
    int beautifulSubstrings(string s, int k) {
        int n = s.size();
        vector<int> v(n), pre(n);
        for (int i = 0; i < n; ++i) {
            v[i] = ('a' == s[i] || 'e' == s[i] || 'i' == s[i] || 'o' == s[i] || 'u' == s[i]) ? 1 : -1;
            if (0 < i) {
                pre[i] = pre[i - 1] + v[i];
            } else {
                pre[i] = v[i];
            }
        }
        int res = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = i; j < n; ++j) {
                int sum = (0 == i ? pre[j] : pre[j] - pre[i - 1]);
                if (0 == sum && 0 == ((j - i + 1) / 2) * ((j - i + 1) / 2) % k) {
                // if (0 == sum && 0 == (int)pow((j - i + 1) / 2, 2) % k) {
                    ++res;
                }
            }
        }
        return res;
    }
};

int main() {
    string s = "baeyh";
    int k = 2;
    cout << Solution().beautifulSubstrings(s, k) << endl;
    return 0;
}