#include "D:\distake\Coding\head_file.h"

class Solution {
public:
    int fourSumCount(vector<int>& nums1, vector<int>& nums2, vector<int>& nums3, vector<int>& nums4) {
        unordered_map<int, int> unmap;
        for (auto& a : nums1) {
            for (auto& b : nums2) {
                unmap[a + b]++;
            }
        }
        int count = 0;
        for (auto& c : nums3) {
            for (auto& d : nums4) {
                if (unmap.find(-(c + d)) != unmap.end()) {
                    count += unmap[-(c + d)];
                }
            }
        }
        return count;
    }
};

int main() {
    Solution s;
    vector<int> v1 {1, 2}, v2{ -2,-1 }, v3{ -1,2 }, v4{ 0,2 };
    cout << s.fourSumCount(v1, v2, v3, v4);
    return 0;
}