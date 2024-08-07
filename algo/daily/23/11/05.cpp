#include "../../head_file.h"

/*
problme: 

url: 
 */

// time complexity: O()
// spatial complexity: O()
class Solution {
public:
    vector<string> findRepeatedDnaSequences(string s) {
        int n = s.size();
        if (10 > n) {
            return {};
        }
        int i = 0, j = 0;
        unordered_map<string, int> m;
        unordered_set<string> res;
        while (j < n) {
            while (10 > j - i + 1) {
                ++j;
            }
            string sub(s.begin() + i, s.begin() + j + 1);
            if (m.count(sub)) {
                res.insert(sub);
            }
            m[sub] = 1;
            ++i;
        }
        return vector<string>(res.begin(), res.end());
    }
};

int main() {
    // string s = "AAAAAAAAAAAAA";
    string s = "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT";
    auto res = Solution().findRepeatedDnaSequences(s);
    for (const auto &str : res) {
        cout << str << endl;
    }
    return 0;
}