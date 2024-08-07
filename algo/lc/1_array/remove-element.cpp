#include "../../head_file.h"

// remove element

class ViolentSolution {
public:
    int removeElement(vector<int>& nums, int val) {
        int repeat = 0;
        for (int i = 0; i < nums.size(); ++i) {
            if (val == nums[i]) {
                repeat++;
                for (int j = i; j < nums.size() - 1; ++j) {
                    nums[j] = nums[j + 1];
                }
                --i; // 
            }
        }
        return nums.size() - repeat;
    }
};

class DoublePoint {
public:
    int removeElement(vector<int>& nums, int val) {
        int left = 0;
        for (int right = 0; right < nums.size(); ++right) {
            if (nums[right] != val) {
                nums[left] = nums[right];
                ++left;
            }
        }
        return left;
    }
};

int main() {
    vector<int> v { 2, 3, 3, 2};

    return 0;
}