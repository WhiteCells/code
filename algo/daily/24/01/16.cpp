#include "../../head_file.h"

/*
problme:
输入：words = ["cd","ac","dc","ca","zz"]
输出：2
url: https://leetcode.cn/problems/find-maximum-number-of-string-pairs
 */

class Solution {
public:
    int maximumNumberOfStringPairs(vector<string> &words) {
        int res = 0;
        unordered_set<string> st;
        for (auto &str : words) {
            if (st.count(str)) {
                ++res;
            } else {
                reverse(str.begin(), str.end());
                st.insert(str);
            }
        }
        return res;
    }
};

int main() {
    vector<string> words {"cd", "ac", "dc", "ca", "zz"};
    cout << Solution().maximumNumberOfStringPairs(words) << endl;
    return 0;
}