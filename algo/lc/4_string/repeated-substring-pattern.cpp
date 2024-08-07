#include "D:\distake\Coding\head_file.h"

class Solution {
public:
    bool repeatedSubstringPattern(string s) {
        string double_str = s + s;
        double_str.erase(double_str.begin());
        double_str.erase(double_str.end() - 1);
        if (double_str.find(s) != std::string::npos) {
            return true;
        }
        return false;
    }
};

class Solution2 {
public:
    bool repeatedSubstringPattern(string s) {

    }
};

int main() {
    Solution s;
    string str = "abab";
    cout << s.repeatedSubstringPattern(str);
    return 0;
}