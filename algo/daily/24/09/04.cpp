#include "../../head_file.h"

/*
problme:

url:
 */

class Solution
{
public:
    long long maxStrength(vector<int> &nums)
    {
        sort(nums.begin(), nums.end());
        int ne = count_if(nums.begin(), nums.end(), [](int num) {
            return num < 0;
        });
        int po = count_if(nums.begin(), nums.end(), [](int num) {
            return num > 0;
        });
        long long res1 = 1;
        int i = 0;
        while (ne >= 2) {
            res1 *= nums[i++];
            res1 *= nums[i++];
            ne -= 2;
        }
        int j = nums.size() - 1;
        long long res2 = 1;
        bool flag = false;
        while (j >= nums.size() - po && nums[j] > 0) {
            flag = true;
            res2 *= nums[j--];
        }
        return flag ? res2 : 0;
    }
};

class Solution2
{
public:
    int countWays(vector<int> &nums)
    {
        int n = nums.size();
        int res = 0;
        sort(nums.begin(), nums.end());
        for (int k = 0; k <= n; k++) {
            if (k > 0 && nums[k - 1] >= k) {
                continue;
            }
            if (k < n && nums[k] <= k) {
                continue;
            }
            res++;
        }
        return res;
    }
};

int main()
{
    std::vector<int> nums {0, -1};
    std::cout << Solution().maxStrength(nums);
    return 0;
}