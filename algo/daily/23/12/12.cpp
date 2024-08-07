#include "../../head_file.h"

/*
problme:

url:
 */

class Solution {
public:
    vector<int> secondGreaterElement(vector<int> &nums) {
        int n = nums.size();
        vector<int> res(n, -1), s1, s2;
        for (int i = 0; i < n; ++i) {
            while (!s2.empty() && nums[i] > nums[s2.back()]) {
                res[s2.back()] = nums[i];
                s2.pop_back();
            }
            // 单调栈 s1 中比当前值小的范围
            int j = s1.size() - 1;
            while (j >=0 && nums[i] > nums[s1[j]]) {
                --j;
            }
            s2.insert(s2.end(), s1.begin() + j + 1, s1.end());
            s1.resize(j + 1);
            s1.emplace_back(i);
        }
        return res;
    }
};

int main() {
    vector<int> nums {2, 4, 0, 9, 6};
    auto res = Solution().secondGreaterElement(nums);
    for (const auto &ele : res) {
        cout << ele << ' ';
    }
    return 0;
}