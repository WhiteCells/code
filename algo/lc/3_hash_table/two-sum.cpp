#include "D:\distake\Coding\head_file.h"

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> unmap;
        for (int i = 0; i < nums.size(); ++i) {
            // unordered_map<int, int>::iterator iter = unmap.find(target - nums[i]);
            auto iter = unmap.find(target - nums[i]);
            if (iter != unmap.end()) {
                return { i, iter->second };
            }
            unmap.insert(pair<int, int>(nums[i], i));
        }
        return {};
    }
};

int main() {
    Solution s;
    vector<int> v {1, 3, 2, 5};
    vector<int> ret = s.twoSum(v, 8);
    for (auto& val : ret) {
        cout << val << " ";
    }
    return 0;
}