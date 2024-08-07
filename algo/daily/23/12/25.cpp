#include "../../head_file.h"

/*
problme: 

url: 
 */

class Solution {
public:
    vector<int> numOfBurgers(int tomatoSlices, int cheeseSlices) {
        int right = tomatoSlices - 2 * cheeseSlices;
        int res1 = right / 2, res2 = cheeseSlices - res1;
        if (right < 0 || res1 < 0 || res2 < 0) {
            return {};
        }
        return 0 == right % 2 ? vector<int>{res1, res2} : vector<int>{};
    }
};

int main() {
    // int t = 2385088, c = 164763;
    int t = 16, c = 7;
    auto res = Solution().numOfBurgers(t, c);
    if (!res.empty()) {
        cout << res[0] << ' ' << res[1] << endl;
    }
    return 0;
}