#include "../../head_file.h"

/*
problme: 

url: https://leetcode.cn/problems/longest-uncommon-subsequence-i/
 */

class Solution {
public:
    int findLUSlength(string a, string b) {
        // abab ababacdcddbd
        if (a == b) {
            return -1;
        }
        return max(a.size(), b.size());
    }
};

int main() {
    // string a = "aba", b = "cdc";
    string a = "aba", b = "abababab";
    cout << Solution().findLUSlength(a, b) << endl;
    return 0;
}