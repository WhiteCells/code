#include "../../head_file.h"

/*
problme:

url:
 */

class Solution
{
public:
    vector<int> sortedSquares(vector<int> &nums)
    {
        int n = nums.size();
        vector<int> res(n);
        int i = 0, j = n - 1;
        int k = j;
        while (i <= j) {
            if (abs(nums[i]) > abs(nums[j])) {
                res[k] = nums[i] * nums[i];
                ++i;
            }
            else {
                res[k] = nums[j] * nums[j];
                --j;
            }
            --k;
        }
        return res;
    }
};

int main()
{
    vector<int> nums {-5, -3, -2, -1};
    auto res = Solution().sortedSquares(nums);
    for (const auto &ele : res) {
        cout << ele << endl;
    }
    return 0;
}