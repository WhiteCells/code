#include "D:\distake\Coding\head_file.h"

class Solution {
public:
    bool isAnagram(string s, string t) {
        int arr[26] = { 0 };
        for (int i = 0; i < s.size(); ++i) ++arr[s[i] - 'a'];
        for (int i = 0; i < t.size(); ++i) --arr[t[i] - 'a'];
        for (int i = 0; i < 26; ++i) if (arr[i]) return false;
        return true;
    }
    bool isAnagram1(string s, string t) {
        int arr[26] = { 0 };
        for (int i = 0; i < s.size(); ++i)
            ++arr[s[i] - 'a'];
        for (int i = 0; i < t.size(); ++i) {
            --arr[t[i] - 'a'];
            if (arr[t[i] - 'a'] < 0) {
                return false;
            }
        }
        return true;
    }
    bool isAnagram2(string s, string t) {
        if (s.size() != t.size()) return false;
        vector<int> table(26, 0);
        for (auto& ch : s) {
            ++table[ch - 'a'];
        }
        for (auto& ch : t) {
            --table[ch - 'a'];
            if (table[ch - 'a'] < 0) return false;
        }
        return true;
    }
};

int main() {
    string s1, s2;
    s1 = "angaram";
    s2 = "angaran";
    Solution s;
    if (s.isAnagram1(s1, s2)) {
        cout << "isAnagram" << endl;
    }
    else {
        cout << "noAnagram" << endl;
    }
    return 0;
}