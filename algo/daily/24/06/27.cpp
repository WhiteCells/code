#include "../../head_file.h"

/*
problme: 

url: https://leetcode.cn/problems/lexicographically-smallest-string-after-substring-operation
 */

class Solution {
public:
    string smallestString(string s) {
        int n = s.size();
        for (int i = 0; i < n; ++i) {
            if (s[i] > 'a') {
                for (; i < n && s[i] > 'a'; ++i) {
                    s[i] -= 1;
                }
                return s;
            }
        }
        s.back() = 'z';
        return s;
    }
};

int main() {
    string s = "aaaaa";
    string s = "aaaaa";
    cout << Solution().smallestString(s) << endl;

    float x = 1.1;
    if (x == 0.0f) {
        
    }
    return 0;
}