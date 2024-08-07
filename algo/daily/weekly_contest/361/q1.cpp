#include "../../head_file.h"

/*
problme:

url:
*/

class Solution {
public:
    int StringToInt(string& s) {
        int n = s.size();
        int res = 0;
        for (int i = 0; i < n; ++i) {
            res += (s[i] - '0');
        }
        return res;
    }
    bool IsSqrt(int val) {
        for (int i = 0; i <= 10; ++i) {
            if (val == pow(2, i)) {
                return true;
            }
        }
        return false;
    }
public:
    int countSymmetricIntegers(int low, int high) {
        int cnt = 0;
        for (int i = low; i <= high; ++i) {
            string s = to_string(i);
            int n = s.size();
            if (IsSqrt(n)) {
                int mid = n / 2;
                string s1 = s.substr(0, mid);
                string s2 = s.substr(mid);
                int val1 = StringToInt(s1);
                int val2 = StringToInt(s2);
                if (val1 == val2) {
                    ++cnt;
                }
            }
        }
        return cnt;
    }
};

int main() {
    cout << Solution().countSymmetricIntegers(1200, 1230) << '\n';
    return 0;
}