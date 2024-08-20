#include "../../head_file.h"

/*
problme: 

url: 
 */

class Solution {
public:
    int addedInteger(vector<int> &nums1, vector<int> &nums2) {
        auto nums1_max = max_element(nums1.begin(), nums1.end());
        auto nums2_max = max_element(nums2.begin(), nums2.end());
        return *nums2_max - *nums1_max;
    }
};


int main() {
    vector<int> nums1 {2,6,4};
    vector<int> nums2 {9,7,5};

    cout << Solution().addedInteger(nums1, nums2) << endl;
    return 0;
}