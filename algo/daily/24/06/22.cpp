#include "../../head_file.h"

/*
problme:

url: https://leetcode.cn/problems/lexicographically-smallest-beautiful-string/description/
 */

class Solution1 {
public:
    string smallestBeautifulString(string s, int k) {
        // s[i] != s[i - 1] && s[i] != s[i - 2]
        // s[i] + 1 < 'a' + k

        auto carry = [&](int idx) -> bool {
            bool car = false;
            for (int i = idx - 1; i >= 0; --i) {
                // 0
                if (car && s[i] + 1 > 'a' + k) {
                    return false;
                }
                if (car) {
                    if (s[i] + 1 > 'a' + k) {
                        car = true;
                        s[i] = 'a';
                    } else {
                        car = false;
                        ++s[i];
                    }
                } else {
                    if (s[i] + 1 > 'a' + k) {
                        car = true;
                        s[i] = 'a';
                    } else {
                        ++s[i];
                    }
                }
            }
            return true;
        };

        int n = s.size();
        for (int i = 1; i < n; ++i) {
            if (i == 1 && s[i] == s[i - 1]) {
                if (!carry(i)) {
                    return "";
                }
                continue;
            }
            if (s[i] == s[i - 1] || s[i] == s[i - 2]) {
                if (!carry(i)) {
                    return "";
                }
            }
        }
        return s;
    }
};

class Solution {
public:
    string smallestBeautifulString(string s, int k) {
        int n = s.size();
        int i = n - 1;
        ++s[i];
        while (i < n) {
            if (s[i] == 'a' + k) {
                if (i == 0) {
                    return "";
                }
                s[i] = 'a';
                --i;
                ++s[i];
            } else if (i && s[i] == s[i - 1] || i > 1 && s[i] == s[i - 2]) {
                s[i]++;
            } else {
                i++;
            }
        }
        return s;
    }
};

int main() {
    string s = "abcz";
    int k = 26;
    cout << Solution().smallestBeautifulString(s, k) << endl;
    return 0;
}