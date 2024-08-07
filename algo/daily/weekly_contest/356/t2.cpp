#include "../../head_file.h"

// https://leetcode.cn/problems/count-complete-subarrays-in-an-array/

// 原状
// O(n^2)
class Solution {
public:
    int countCompleteSubarrays(vector<int>& nums) {
        int cnt = 0; // 统计 nums 中不同的元素个数
        int a[2001]{};
        for (auto& num : nums) {
            if (!a[num]) {
                ++cnt;
            }
            a[num] = 1;
        }
        int ans = 0;
        for (int i = 0; i < nums.size(); ++i) {
            int mp[2001]{}, cur = 0;
            for (int j = i; j < nums.size(); ++j) {
                if (!mp[nums[j]]) {
                    ++cur;
                    mp[nums[j]] = 1;
                }
                if (cur == cnt) {
                    ++ans;
                }
                else if (cur > cnt) { // cur 不可能大于 cnt
                    break;
                }
            }
        }
        return ans;
    }
};


// O(n)
// 滑窗
class Solution2 {
public:
    int countCompleteSubarrays(vector<int>& nums) {
        int cnt = 0;
        int t[2001]{};
        for (const auto& num : nums) {
            if (!t[num]) {
                ++cnt;
                t[num] = 1;
            }
        }
        int left = 0, ans = 0;
        unordered_map<int, int> mp;
        for (const auto& num : nums) {
            ans += left;
            ++mp[num];
            while (mp.size() == cnt) { // while 执行完，窗口不满足要求
                ++ans;
                --mp[nums[left]]; // 删除左端点
                if (!mp[nums[left]]) {
                    mp.erase(nums[left]);
                }
                ++left; // 移动 left
            }
        }
        return ans;
    }
};

// 12 ms, 30 mb
class Solution3 {
public:
    int countCompleteSubarrays(vector<int>& nums) {
        int cnt = 0, tb[2001]{};
        for (const auto& num : nums) {
            if (!tb[num]) {
                ++cnt;
                tb[num] = 1;
            }
        }
        int left = 0, ans = 0, tb2[2001]{}, cur = 0;
        for (const auto& num : nums) {
            ans += left;
            if (!tb2[num]) {
                ++cur;
            }
            ++tb2[num];
            while (cur == cnt) {
                ++ans;
                --tb2[nums[left]];
                if (!tb2[nums[left]]) {
                    --cur;
                }
                ++left;
            }
        }
        return ans;
    }
};

int main() {
    Solution3 s;
    auto nums = vector<int>{ 1, 3, 1, 2, 2 };
    cout << s.countCompleteSubarrays(nums);
    return 0;
}