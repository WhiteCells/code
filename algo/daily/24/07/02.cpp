#include "../../head_file.h"

/*
problme:

url:
 */

class Solution {
public:
    int maximumPrimeDifference(vector<int> &nums) {
        int start = 0, end = 0;
        bool first = true;
        for (int i = 0; i < nums.size(); ++i) {
            if (isPrime(nums[i])) {
                if (first) {
                    start = i;
                    first = false;
                } else {
                    end = i;
                }
            }
        }
        return end - start;
    }
private:
    bool isPrime(int num) {
        for (int i = 2; i < num; ++i) {
            if (num % i == 0) {
                return false;
            }
        }
        return true;
    }
};

int main() {
    vector<int> nums {4,8,2,8};
    cout << Solution().maximumPrimeDifference(nums) << endl;
    return 0;
}