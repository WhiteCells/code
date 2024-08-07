#include "../../head_file.h"

/*
problme:

url:
 */

class Solution {
public:
    int findPeakElement(vector<int> &nums) {
        vector<int> v;
        v.push_back(INT_MIN);
        for (const auto &num : nums) {
            v.push_back(num);
        }
        v.push_back(INT_MIN);
        for (int i = 1; i + 1 < nums.size(); ++i) {
            if (v[i] > v[i - 1] && v[i] > v[i + 1]) {
                return i - 1;
            }
        }
        return -1;
    }
};

int main() {
    vector<int> nums {1, 2, 1, 3, 5, 6, 4};
    cout << Solution().findPeakElement(nums) << endl;
    return 0;
}