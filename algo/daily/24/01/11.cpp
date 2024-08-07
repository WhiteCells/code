#include "../../head_file.h"

/*
problme:

url: https://leetcode.cn/problems/count-common-words-with-one-occurrence/
 */

class Solution {
public:
    int countWords(vector<string> &words1, vector<string> &words2) {
        unordered_map<string, int> mp1, mp2;
        for (const auto &str : words1) {
            ++mp1[str];
        }
        for (const auto &str : words2) {
            ++mp2[str];
        }
        int res = 0;
        for (const auto &[s, n] : mp1) {
            if (1 == n && 1 == mp2[s]) {
                ++res;
            }
        }
        return res;
    }
};

int main() {
    /*
    words1 =
    ["a","ab"]
    words2 =
    ["a","a","a","ab"]
     */
    vector<string> word1 {"a", "ab"};
    vector<string> word2 {"a", "a", "a", "ab"};
    cout << Solution().countWords(word1, word2) << endl;
    return 0;
}