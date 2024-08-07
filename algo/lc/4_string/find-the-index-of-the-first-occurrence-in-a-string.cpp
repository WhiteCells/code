#include "D:\distake\Coding\head_file.h"

class Solution {
public:
    void getNext(int* next, const string& s) {
        int j = -1;
        next[0] = -1;
        for (int i = 1; i < s.size(); ++i) {
            while (j >= 0 && s[i] != s[j + 1]) {
                j = next[j];
            }
            if (s[i] == s[j + 1]) {
                ++j;
            }
            next[i] = j;
        }
    }
    int strStr(string haystack, string needle) {
        int next[needle.size()];
        getNext(next, needle);
        /* */
        for (int i = 0; i < needle.size(); ++i) {
            cout << next[i] << " ";
        }
        cout << endl;
        /* */
        int j = -1;
        for (int i = 0; i < haystack.size(); ++i) {
            while (j >= 0 && haystack[i] != needle[j + 1]) {
                j = next[j];
            }
            if (haystack[i] == needle[j + 1]) {
                ++j;
            }
            if (j == needle.size() - 1) {
                return i - needle.size() + 1;
            }
        }
        return -1;
    }
};

int main() {
    Solution s;
    string s1 = "abcdabdc";
    string s2 = "abd";
    cout << s.strStr(s1, s2);
    return 0;
}