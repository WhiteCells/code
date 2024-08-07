#include "D:\distake\Coding\head_file.h"

// next[0] == -1
// next 表示最长相等的前后缀长度
void getNext(int* next, const string& s) {
    int j = -1;
    next[0] = -1;
    for (int i = 1; i < s.size(); ++i) {
        // 前后缀不相等
        while (j >= 0 && s[i] != s[j + 1]) {
            j = next[j]; // 向前回退
        }
        // 相同的前后缀
        if (s[i] == s[j + 1]) {
            ++j;
        }
        next[i] = j; // 将前后缀长度赋值给 next[i]
    }
}

int strStr(string haystack, string needle) {
    int next[needle.size()];
    getNext(next, needle);
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

// next[0] == 0
void getNext2(int* next, const string& s) {
    int j = 0;
    next[0] = 0;
    for (int i = 1; i < s.size(); ++i) {
        while (j > 0 && s[i] != s[j]) {
            j = next[j - 1];
        }
        if (s[i] == s[j]) {
            ++j;
        }
        next[i] = j;
    }
}

int strStr2(string haystack, string needle) {
    int next[needle.size()];
    getNext2(next, needle);
    int j = 0;
    for (int i = 0; i < haystack.size(); ++i) {
        while (j > 0 && haystack[i] != needle[j]) {
            j = next[j - 1];
        }
        if (haystack[i] == needle[j]) {
            ++j;
        }
        if (j == needle.size()) {
            return i - needle.size() + 1;
        }
    }
    return -1;
}

class Solution {
public:
    void getNext(int* next, const string& sub) {

    }
};

int main() {
    string s1 = "ababcabe";
    string s2 = "abe";
    cout << strStr2(s1, s2);
    return 0;
}