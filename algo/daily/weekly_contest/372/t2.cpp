#include "../../head_file.h"

/*
problme:

url: https://leetcode.cn/problems/separate-black-and-white-balls/description/
 */

// 前缀和
class Solution {
public:
    long long minimumSteps(string s) {
        long long res = 0;
        vector<int> pre(s.size());
        pre[0] = ('1' == s[0] ? 1 : 0);
        for (int i = 1; i < s.size(); ++i) {
            pre[i] = pre[i - 1] + ('1' == s[i] ? 1 : 0);
            if ('0' == s[i]) {
                res += pre[i];
            }
        }
        return res;
    }
};

class Solution2 {
public:
    long long minimumSteps(string s) {
        long long res = 0;
        int cnt = 0;
        for (int i = 0; i < s.size(); ++i) {
            if ('1' == s[i]) {
                ++cnt;
            } else {
                res += cnt;
            }
        }
        return res;
    }
};

int main() {
    cout << Solution2().minimumSteps("101") << endl;
    return 0;
}