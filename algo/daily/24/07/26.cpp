#include "../../head_file.h"

/*
problme:

url:
 */

class Solution {
public:
    int findValueOfPartition(vector<int> &nums) {
        int min1 = INT_MAX, min2 = -1;
        // 3 5 2 1 0
        // 3
        // 3
        //   3
        //   3
        //     2
        //     3
        //       1
        //       2
        // for (const int num : nums) {
        //     // if (num < min1) {
        //     //     int tmp = min1;
        //     //     min1 = num;
        //     //     if (num < min2) {
        //     //         min2 = (tmp == INT_MAX ? num : tmp);
        //     //     }
        //     // }
        //     if (num < min1) {
        //         min1 = num;
        //     }
        //     if (num > min2) {
        //         min2 = min(num, min2);
        //     }
        // }
        // return min2 - min1;
    }
};

int main() {
    vector<int> nums {1, 3, 2, 4};
    cout << Solution().findValueOfPartition(nums) << endl;
    return 0;
}