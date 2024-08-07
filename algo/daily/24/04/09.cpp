#include "../../head_file.h"

/*
problme:

url:
 */

class Solution {
public:
    int maximumCount(vector<int> &nums) {
        int n = nums.size();
        int left = 0, right = nums.size() - 1;
        auto lowerBound = [&nums, left, right]() mutable -> int {
            while (left <= right) {
                int mid = left + ((right - left) >> 1);
                if (nums[mid] >= 0) {
                    right = mid - 1;
                } else {
                    left = mid + 1;
                }
            }
            return left;
        };
        auto upperBound = [&nums, left, right]() mutable -> int {
            while (left <= right) {
                int mid = left + ((right - left) >> 1);
                if (nums[mid] > 0) {
                    right = mid - 1;
                } else {
                    left = mid + 1;
                }
            }
            return left;
        };
        int left_zero_min_index = lowerBound();
        int right_zero_max_index = upperBound();
        return max(left_zero_min_index, n - right_zero_max_index);
    }
};

int main() {
    vector<int> nums {-3,-2,-1,0,0,1,2};
    int res = Solution().maximumCount(nums);
    std::cout << res << std::endl;
    return 0;
}