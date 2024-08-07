#include "../../head_file.h"

/*
problme:

url: https://leetcode.cn/problems/make-three-strings-equal/description/
 */

class Solution {
public:
    int findMinimumOperations(string s1, string s2, string s3) {
        if (s1[0] != s2[0] || s2[0] != s3[0]) {
            return -1;
        }
        int mn = min({s1.size(), s2.size(), s3.size()});
        int i = 0;
        while (i < mn) {
            if (s1[i] != s2[i] || s2[i] != s3[i]) {
                break;
            }
            ++i;
        }
        return int(s1.size() + s2.size() + s3.size()) - 3 * i;
    }
};

int main() {
    // string s1 = "abc", s2 = "abb", s3 = "ab";
    string s1 = "bcbb", s2 = "bccbabb", s3 = "bcabb";
    cout << Solution().findMinimumOperations(s1, s2, s3) << endl;
    return 0;
}