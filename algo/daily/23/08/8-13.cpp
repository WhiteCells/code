#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
// https://leetcode.cn/problems/merge-sorted-array/description/

class Solution1 {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        for (int i = m, j = 0; i < m + n && j < n; ++i, ++j) {
            nums1[i] = nums2[j];
        }
        sort(nums1.begin(), nums1.end());
    }
};

class Solution2 {
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int index1 = m - 1;
        int index2 = n - 1;
        int cnt = m + n;
        while (cnt--) {
            if (index1 < 0) {
                for (int i = 0; i < index2; ++i) {
                    nums1[i] = nums2[i];
                }
                break;
            }
            if (index2 < 0) {
                break;
            }
            if (nums1[index1] > nums2[index2]) {
                nums1[cnt] = nums1[index1--];
            }
            else {
                nums1[cnt] = nums2[index2--];
            }
        }
    }
};


int main() {

    return 0;
}