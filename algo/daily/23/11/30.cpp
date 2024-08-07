#include "../../head_file.h"

/*
problme:

url: https://leetcode.cn/problems/determine-if-two-strings-are-close/description/
 */

class Solution {
public:
    bool closeStrings(string word1, string word2) {
        if (word1.size() != word2.size()) {
            return false;
        }
        vector<int> arr1(26), arr2(26), mp(26);
        for (int i = 0; i < word1.size(); ++i) {
            ++arr1[word1[i] - 'a'];
            mp[word1[i] - 'a'] = 1;
        }
        for (int i = 0; i < word1.size(); ++i) {
            ++arr2[word2[i] - 'a'];
            if (!mp[word2[i] - 'a']) {
                return false;
            }
        }
        sort(arr1.begin(), arr1.end());
        sort(arr2.begin(), arr2.end());
        for (int i = 0; i < arr1.size(); ++i) {
            if (arr1[i] != arr2[i]) {
                return false;
            }
        }
        return true;
    }
};

int main() {
    // string word1 {"cabbba"}, word2 {"aabbss"};
    string word1 {"uau"}, word2 {"ssx"};
    cout << Solution().closeStrings(word1, word2) << endl;
    return 0;
}