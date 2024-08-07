#include "../../head_file.h"

/*
problme: 

url: 
 */

class Solution {
public:
    int findLUSlength(vector<string>& strs) {
        // str1 是否为 str2 的子序列
        auto isSub = [&](const string &str1, const string &str2) -> bool {
            int j = 0;
            for (int i = 0; i < str2.size(); ++i) {
                if (str1[j] == str2[i]) {
                    ++j;
                }
            }
            return j == str1.size();
        };

        int res = -1;
        for (int i = 0; i < strs.size(); ++i) {
            bool flag = true;
            if (strs[i].size() > res) { // bug
                for (int j = 0; j < strs.size(); ++j) {
                    if (j != i && isSub(strs[i], strs[j])) {
                        flag = false;
                        break;
                    }
                }
                if (flag) {
                    res = strs[i].size();
                }
            }
        }

        return res;
    }
};

int main() {
    vector<string> strs {"aba","cdc","eae"};
    cout << Solution().findLUSlength(strs) << endl; // 3
    return 0;
}