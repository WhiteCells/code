#include "../../head_file.h"

/*
problme: 

url: 
 */

class Solution {
public:
    string makeSmallestPalindrome(string s) {
        for (int i = 0, j = s.size() - 1; i < j; ++i, --j) {
            if (s[i] > s[j]) {
                s[j] = s[i];
            } else if (s[i] < s[j]) {
                s[i] = s[j];
            }
        }
        return s;
    }
};

int main() {
    cout << Solution().makeSmallestPalindrome("abca") << endl;
    return 0;
}