#include "../../head_file.h"

/*
problme:

url:
*/

class Solution {
public:
    int StringToInt(string& num) {
        int n = num.size();
        int res = 0;
        for (int i = 0; i < n; ++i) {
            res = res * 10 + (num[i] - '0');
        }
        return res;
    }
public:
    int minimumOperations(string num) {
        int n = num.size();
        // 能被 25 整除，这个数必须是 0 或者 5 结尾
        int cnt = 0; // 统计删除次数
        int i = n - 1;
        while (i >= 0) {
            string s = num.substr(0, i + 1);
            if (0 == StringToInt(s) % 25) {
                return cnt;
            }
            else {
                /* 最后一位 5 */
                if ('5' == num[i]) {
                    // 找到一个 2
                    while (i >= 1 && '2' != num[i - 1]) {
                        --i;
                        ++cnt;
                    }
                }
                /* 最后一位 0 */
                else if ('0' == num[i]) {
                    // 找到一个 5 或者 0
                    while (i >= 1 && ('0' != num[i - 1] || '5' != num[i - 1])) {
                        --i;
                        ++cnt;
                    }
                }
            }
        }
        return cnt;
    }
};

int main() {
    // Solution s;
    string s = "2908305";
    cout << Solution().minimumOperations(s) << '\n';
    return 0;
}