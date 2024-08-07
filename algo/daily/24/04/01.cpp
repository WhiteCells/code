#include "../../head_file.h"

/*
problme: 

url: 
 */

class Solution {
public:
    string finalString(string s) {
        string res;
        for (int i = 0; i < s.size(); ++i) {
            if (s[i] == 'i') {
                // reverse(res.begin(), res.begin() + i);
                reverse(res.begin(), res.end());
            } else {
                res += s[i];
            }
        }
        return res;
    }
};

int main() {
    cout << Solution().finalString("string") << std::endl;
    return 0;
}