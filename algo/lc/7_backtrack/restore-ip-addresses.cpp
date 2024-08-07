#include "D:/distake/Coding/head_file.h"


class Solution {
public:
    int stringToInt(const string& s, int start, int end) {
        int res = 0;
        for (int i = end, j = 0; i >= start; --i, ++j) {
            res += (s[i] - '0') * pow(10, j);
        }
        return res;
    }
};


int main() {
    Solution s;
    cout << s.stringToInt("25255", 2, 4);
    return 0;
}