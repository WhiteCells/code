#include "D:\distake\Coding\head_file.h"

class Solution {
public:
    void reverseString(vector<char>& s) {
        int left = 0, right = s.size() - 1;
        while (left < right) {
            char tmp = s[left];
            s[left] = s[right];
            s[right] = tmp;
            left++;
            right--;
        }
    }
};

class Solution2 {
public:
    void reverseString(vector<char>& s) {
        string str;
        for (auto& c : s) {
            str += c;
        }
        str.reserve(s.size());
        for (int i = 0; i < s.size(); ++i) {
            s[i] = str[i];
        }
    }
};

int main() {
    vector<char> str { 'h', 'e', 'l', 'l', 'o' };
    Solution2 s;
    s.reverseString(str);
    for (auto& c : str) {
        cout << c;
    }
    return 0;
}