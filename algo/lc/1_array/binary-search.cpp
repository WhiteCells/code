#include "../../head_file.h"

class Solution {
public:
    int search(vector<int>& nums, int target) {
        int left = 0;
        int mid_index = 0;
        int right = nums.size() - 1;
        while (left <= right) {
            // mid_index = (left + right) >> 2;
            mid_index = (right - left) >> 2 + left;
            if (nums[mid_index] == target) return mid_index;
            else if (nums[mid_index] < target) left = mid_index + 1;
            else right = mid_index - 1;
        }
        return -1;
    }
};

int main() {
    vector<int> v { 1, 3, 5, 7, 9}; // A Simple Example
    Solution s;
    cout << s.search(v, 3);
    return 0;
}