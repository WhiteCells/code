#include <iostream>
#include <vector>

// std::vector<int> nums {2, 1, 0, -1, -2, 4};
void sortRange(std::vector<int> &nums, int start, int end) {
    if (start >= end) {
        return;
    }
    int key = nums[start];
    int left = start, right = end;
    while (left < right) {
        while (nums[right] >= key && left < right) {
            --right;
        }
        while (nums[left] <= key && left < right) {
            ++left;
        }
        std::swap(nums[left], nums[right]);
    }
    if (nums[left] < key) {
        std::swap(nums[left], nums[start]);
    }
    sortRange(nums, start, left - 1);
    sortRange(nums, left + 1, end);
}

void qsort2(std::vector<int> &nums) {
    sortRange(nums, 0, nums.size() - 1);
}

int main(int argc, char *argv[]) {
    std::vector<int> nums {2, 1, 0, -2, -1, 4};
    qsort2(nums);
    for (const auto &num : nums) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    return 0;
}