#include "D:\distake\Coding\head_file.h"

class Solution {
public:
    string replaceSpace(string s) {
        string res;
        for (int i = 0; i < s.size(); ++i) {
            if (s[i] == ' ') {
                res += "%20";
            }
            else {
                res += s[i];
            }
        }
        return res;
    }
    string replaceSpace2(string s) {
        int count = 0;
        for (int i = 0; i < s.size(); ++i) {
            if (s[i] == ' ') ++count;
        }
        int oldSize = s.size();
        s.resize(s.size() + 2 * count);
        int newSize = s.size();
        for (int i = oldSize - 1, j = newSize - 1; i > 0 && j > 0; --i, --j) {
            if (s[i] == ' ') {
                s[j] = '%';
                s[j - 1] = '0';
                s[j - 2] = '2';
                j -= 2;
            }
            else {
                s[j] = s[i];
            }
        }
        return s;
    }
    string replaceSpace3(string s) {
        int count = 0;
        for (auto& c : s) {
            if (c == ' ') {
                ++count;
            }
        }
        int oldSize = s.size();
        s.resize(oldSize + 2 * count);
        int newSize = s.size();
        int left = oldSize - 1, right = newSize - 1;
        while (left != right) {
            if (s[left] == ' ') {
                s[right] = '0';
                s[right - 1] = '2';
                s[right - 2] = '%';
                left--;
                right -= 3;
            }
            else {
                s[right--] = s[left--];
            }
        }
        return s;
    }
};

int main() {
    Solution s;
    string str = "hell o world";
    cout << s.replaceSpace3(str);
    return 0;
}