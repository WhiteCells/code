// https://leetcode.cn/problems/continuous-subarrays/

// 2762. 不间断子数组

// 给你一个下标从 0 开始的整数数组 nums 。nums 的一个子数组如果满足以下条件，那么它是 不间断 的：

//     i，i + 1 ，...，j  表示子数组中的下标。对于所有满足 i <= i1, i2 <= j 的下标对，都有 0 <= |nums[i1] - nums[i2]| <= 2 。

// 请你返回 不间断 子数组的总数目。

// 子数组是一个数组中一段连续 非空 的元素序列。


// 1 <= nums.length <= 10^5
// 1 <= nums[i] <= 10^9


// 输入：nums = [5,4,2,4]
// 输出：8
// 解释：
// 大小为 1 的不间断子数组：[5], [4], [2], [4] 。
// 大小为 2 的不间断子数组：[5,4], [4,2], [2,4] 。
// 大小为 3 的不间断子数组：[4,2,4] 。
// 没有大小为 4 的不间断子数组。
// 不间断子数组的总数目为 4 + 3 + 1 = 8 。
// 除了这些以外，没有别的不间断子数组。


#include "../../head_file.h"


// class Solution {
// public:
//     long long continuousSubarrays(vector<int>& nums) {
//         int left = 0, right = 0, len = nums.size();
//         long long cnt = 0;
//         multiset<int> s;
//         for (auto& num : nums) {
//             s.insert(num);
//             while (*s.rbegin() - *s.begin() > 2) {
//                 s.erase(s.find(nums[left])); // 删除左区间
//                 if (s.find(nums[left]) == s.end()) {

//                 }
//                 left++;
//             }
//         }
//     }
// };

class Solution2 {
public:
    long long continuousSubarrays(vector<int>& nums) {
        int n = nums.size();
        long long ans = 0;

        // 双单调队列维护窗口最大最小
        deque<int> maxq, minq;
        int left = 0; // 左

        for (int right = 0; right < n; ++right) {
            while (!maxq.empty() && nums[maxq.back()] <= nums[right]) {
                maxq.pop_back();
            }
            maxq.push_back(right);
            while (!minq.empty() && nums[minq.back()] >= nums[right]) {
                minq.pop_back();
            }
            minq.push_back(right);
            while (left <= right) {
                if (nums[maxq.front()] - nums[minq.front()] <= 2) {
                    break;
                }
                if (maxq.front() <= left) {
                    maxq.pop_front();
                }
                if (minq.front() <= left) {
                    minq.pop_front();
                }
                ++left;
            }
            ans += right - left + 1;
        }
        return ans;
    }
};

class Solution3 {
public:
    long long continuousSubarrays(vector<int>& nums) {
        multiset<int> s; // 维护左右区间
        long long ans = 0;
        int i = 0, n = nums.size();

        for (int j = 0; j < n; ++j) {
            s.insert(nums[j]);
            while (*s.rbegin() - *s.begin() > 2) {
                s.erase(s.find(nums[i++]));
            }
            ans += j - i + 1;
        }

        return ans;
    }
};

int main() {
    Solution3 s;
    // vector<int> nums{ 5, 4, 2, 4 };
    // vector<int> nums{ 31, 30, 31, 32 };
    vector<int> nums{ 42, 41, 42, 41, 41, 40, 39, 38 };

    cout << s.continuousSubarrays(nums);
    return 0;
}