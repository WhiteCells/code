#include "../head_file.h"
/*
 * @lc app=leetcode.cn id=4 lang=cpp
 *
 * [4] 寻找两个正序数组的中位数
 *
 * https://leetcode.cn/problems/median-of-two-sorted-arrays/description/
 *
 * algorithms
 * Hard (41.57%)
 * Likes:    6707
 * Dislikes: 0
 * Total Accepted:    991.1K
 * Total Submissions: 2.4M
 * Testcase Example:  '[1,3]\n[2]'
 *
 * 给定两个大小分别为 m 和 n 的正序（从小到大）数组 nums1 和 nums2。请你找出并返回这两个正序数组的 中位数 。
 *
 * 算法的时间复杂度应该为 O(log (m+n)) 。
 *
 *
 *
 * 示例 1：
 *
 *
 * 输入：nums1 = [1,3], nums2 = [2]
 * 输出：2.00000
 * 解释：合并数组 = [1,2,3] ，中位数 2
 *
 *
 * 示例 2：
 *
 *
 * 输入：nums1 = [1,2], nums2 = [3,4]
 * 输出：2.50000
 * 解释：合并数组 = [1,2,3,4] ，中位数 (2 + 3) / 2 = 2.5
 *
 *
 *
 *
 *
 *
 * 提示：
 *
 *
 * nums1.length == m
 * nums2.length == n
 * 0 <= m <= 1000
 * 0 <= n <= 1000
 * 1 <= m + n <= 2000
 * -10^6 <= nums1[i], nums2[i] <= 10^6
 *
 *
 */

// @lc code=start
class Solution {
public:
    /* sort */
    /* time complexity:  O(n) + O(nlogn) + O(n) */
    /* sapce complexity: O(1) */
    // double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
    //     for (const auto& num : nums2) {
    //         nums1.push_back(num);
    //     }
    //     sort(nums1.begin(), nums1.end());
    //     return nums1.size() & 1 ? nums1[nums1.size() / 2] : (nums1[nums1.size() / 2] + nums1[nums1.size() / 2 - 1]) / 2.0;
    // }

    /* two pointer */
    /* time complexity:  O(m + n) */
    /* sapce complexity: O(m + n) */
    // double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
    //     int i = 0, j = 0, n1 = nums1.size(), n2 = nums2.size(), n = n1 + n2, index = 0;
    //     vector<int> v(n);
    //     while (i < n1 && j < n2) {
    //         if (nums1[i] < nums2[j]) {
    //             v[index++] = nums1[i++];
    //         }
    //         else {
    //             v[index++] = nums2[j++];
    //         }
    //     }
    //     while (i < n1) {
    //         v[index++] = nums1[i++];
    //     }
    //     while (j <  n2) {
    //         v[index++] = nums2[j++];
    //     }
    //     return n & 1 ? v[n >> 1] : (v[n >> 1] + v[(n >> 1) - 1]) / 2.0;
    // }

    /* two point */
    /* time complexity:  O(n1 * n2) */
    /* sapce complexity: O(n2) */
    // double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
    //     int i = 0, n1 = nums1.size(), n2 = nums2.size(), n = n1 + n2;
    //     // edge cases
    //     if (0 == n1) {
    //         return n2 & 1 ? nums2[n >> 1] : (nums2[n >> 1] + nums2[(n >> 1) - 1]) / 2.0;
    //     }
    //     if (0 == n2) {
    //         return n1 & 1 ? nums1[n >> 1] : (nums1[n >> 1] + nums1[(n >> 1) - 1]) / 2.0;
    //     }
    //     nums1.resize(n);
    //     while (i < n1) {
    //         if (nums1[i] > nums2[0]) {
    //             swap(nums1[i], nums2[0]);
    //             // sort nums2
    //             for (int j = 1; j < nums2.size() && nums2[j] < nums2[j - 1]; ++j) {
    //                 swap(nums2[j], nums2[j - 1]);
    //             }
    //         }
    //         ++i;
    //     }
    //     int j = 0;
    //     while (j < n2) {
    //         nums1[i++] = nums2[j++];
    //     }
    //     return n & 1 ? nums1[n >> 1] : (nums1[n >> 1] + nums1[(n >> 1) - 1]) / 2.0;
    // }

    /* gap method */
    /* time complexity:  O((log base 2 power N) * N) */
    /* sapce complexity: O(1) */
    // double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
    //     int n1 = nums1.size(), n2 = nums2.size(), n = n1 + n2;
    //     // edge cases
    //     if (0 == n1) {
    //         return n2 & 1 ? nums2[n2 >> 1] : (nums2[n2 >> 1] + nums2[(n2 >> 1) - 1]) / 2.0;
    //     }
    //     if (0 == n2) {
    //         return n1 & 1 ? nums1[n1 >> 1] : (nums1[n1 >> 1] + nums1[(n1 >> 1) - 1]) / 2.0;
    //     }
    //     int gap = ceil(n / 2.0); // round up
    //     while (gap) {
    //         int i = 0, j = gap;
    //         while (j < n) {
    //             // 'i' and 'j' in nums1
    //             if (i < n1 && j < n1 && nums1[i] > nums1[j]) {
    //                 swap(nums1[i], nums1[j]);
    //             }
    //             // 'i' in nums1 and 'j' in nums2
    //             else if (i < n1 && j >= n1 && nums1[i] > nums2[j - n1]) {
    //                 swap(nums1[i], nums2[j - n1]);
    //             }
    //             // 'i' and 'j' in nums2
    //             else if (i >= n1 && j >= n1 && nums2[i - n1] > nums2[j - n1]) {
    //                 swap(nums2[i - n1], nums2[j - n1]);
    //             }
    //             ++i;
    //             ++j;
    //         }
    //         // edge cases, ceil(gap / 2.0) never becomes 0  
    //         if (1 == gap) {
    //             gap = 0;
    //         }
    //         gap = ceil(gap / 2.0);
    //     }
    //     // odd
    //     if (n & 1) {
    //         // determine whether (n / 2) is in nums1 or nums2
    //         return (n >> 1) < n1 ? nums1[n >> 1] : nums2[(n >> 1) - n1];
    //     }
    //     // even
    //     else {
    //         if ((n >> 1) < n1) {
    //             return (nums1[n >> 1] + nums1[(n >> 1) - 1]) / 2.0;
    //         }
    //         else if ((n >> 1) - 1 < n1) {
    //             return (nums1[(n >> 1) - 1] + nums2[(n >> 1) - n1]) / 2.0;
    //         }
    //         else {
    //             return (nums2[(n >> 1) - n1] + nums2[(n >> 1) - 1 - n1]) / 2.0;
    //         }
    //     }
    // }

    /*  */
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int n1 = nums1.size(), n2 = nums2.size(), n = n1 + n2;
        // edge cases
        if (0 == n1) {
            return n2 & 1 ? nums2[n2 >> 1] : (nums2[n2 >> 1] + nums2[(n2 >> 1) - 1]) / 2.0;
        }
        if (0 == n2) {
            return n1 & 1 ? nums1[n1 >> 1] : (nums1[n1 >> 1] + nums1[(n1 >> 1) - 1]) / 2.0;
        }
        
    }
};
// @lc code=end


int main() {
    vector<int> nums1 { 1, 2 }, nums2 { 3, 4 };
    Solution s;
    cout << s.findMedianSortedArrays(nums1, nums2) << '\n';
    return 0;
}