#include "../../head_file.h"

/*
problme: 

url: 
 */

class Solution {
    static const int mod = 1e9 + 7;
public:
    int minimumPossibleSum(int n, int target) {
        int res = 0;
        int cnt = 0;
        int i = 1;
        set<int> st;
        while (cnt < n) {
            if (st.count(target - i)) {
                ++i;
                continue;
            }
            st.insert(i);
            res += i;
            res %= mod;
            ++cnt;
            ++i;
        }
        return res;
    }
};

int main() {
    cout << Solution().minimumPossibleSum(3, 3) << endl;
    return 0;
}