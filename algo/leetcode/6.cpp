#include "../head_file.h"

/*
problme:

url:
 */

class Solution {
public:
    string convert(string s, int numRows) {
        if (1 == numRows) {
            return s;
        }
        string res;
        int max_step = (numRows - 1) * 2;
        for (int i = 0; i < s.size(); i += max_step) {
            res += s[i];
        }
        /*
            P     I    N
            A   L S  I G
            Y A   H R
            P     I
         */
        for (int start = 1; start + 1 < numRows; ++start) {
            bool flag = false;
            int step = (numRows - start - 1) * 2;
            for (int i = start; i < s.size(); i += flag ? step : max_step - step) {
                res += s[i];
                flag = !flag;
            }
        }
        for (int i = numRows - 1; i < s.size(); i += max_step) {
            res += s[i];
        }
        return res;
    }
};

int main() {
    string s = "PAYPALISHIRING"; // "PINALSIGYAHRPI"
    int numRows = 4;
    cout << Solution().convert(s, numRows) << endl;
    return 0;
}