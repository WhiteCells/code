#include "../../head_file.h"

// https://leetcode.cn/problems/next-greater-element-i/

// nums1 中数字 x 的 下一个更大元素 是指 x 在 nums2 中对应位置 右侧 的 第一个 比 x 大的元素。
// 输入：nums1 = [4,1,2], nums2 = [1,3,4,2].
// 输出：[-1,3,-1]
// 输入：nums1 = [2,4], nums2 = [1,2,3,4].
// 输出：[3,-1]

// 暴力
class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size(), m = nums2.size();
        vector<int> res(n, -1);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (nums1[i] == nums2[j]) {
                    for (int k = j + 1; k < m; ++k) {
                        if (nums2[k] > nums1[i]) {
                            res[i] = nums2[k];
                            break;
                        }
                    }
                    break;
                }
            }
        }
        return res;
    }
    vector<int> nextGreaterElement2(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size(), m = nums2.size();
        vector<int> res(n, -1);
        unordered_map<int, int> mp;
        for (int i = 0; i < m; ++i) {
            mp[nums2[i]] = i;
        }
        for (int i = 0; i < n; ++i) {
            for (int j = mp[nums1[i]] + 1; j < m; ++j) {
                if (nums2[j] > nums1[i]) {
                    res[i] = nums2[j];
                    break;
                }
            }
        }
        return res;
    }
};

// 单调栈
class Solution2 {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size(), m = nums2.size();
        unordered_map<int, int> mp;
        for (int i = 0; i < n; ++i) {
            mp[nums1[i]] = i;
        }
        stack<int> s;
        vector<int> res(n, -1);
        for (int i = 0; i < m; ++i) {
            while (!s.empty() && nums2[i] > nums2[s.top()]) {
                if (mp.find(nums2[s.top()]) != mp.end()) {
                    res[mp[nums2[s.top()]]] = nums2[i];
                }
                s.pop();
            }
            s.push(i);
        }
        return res;
    }
};

int main() {
    Solution s;
    Solution2 s2;

    // vector<int> nums1 { 4, 1, 2 }, nums2 { 1, 3, 4, 2 };
    vector<int> nums1 { 1, 3, 5, 2, 4 }, nums2 { 6, 5, 4, 3, 2, 1, 7 };

    // auto res = s.nextGreaterElement2(nums1, nums2);
    auto res2 = s2.nextGreaterElement(nums1, nums2);

    // for (auto& ele : res) {
    for (auto& ele : res2) {
        cout << ele << ' ';
    }
    cout << '\n';
    return 0;
}