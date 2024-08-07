#include "../../head_file.h"

/*
problme:2834. 找出美丽数组的最小和
给你两个正整数：n 和 target 。

如果数组 nums 满足下述条件，则称其为 美丽数组 。

    nums.length == n.
    nums 由两两互不相同的正整数组成。
    在范围 [0, n-1] 内，不存在 两个 不同 下标 i 和 j ，使得 nums[i] + nums[j] == target 。

返回符合条件的美丽数组所可能具备的 最小 和。

输入：n = 2, target = 3
输出：4
解释：nums = [1,3] 是美丽数组。
- nums 的长度为 n = 2 。
- nums 由两两互不相同的正整数组成。
- 不存在两个不同下标 i 和 j ，使得 nums[i] + nums[j] == 3 。
可以证明 4 是符合条件的美丽数组所可能具备的最小和。

提示：

    1 <= n <= 105
    1 <= target <= 105

url: https://leetcode.cn/problems/find-the-minimum-possible-sum-of-a-beautiful-array/
*/

class Solution1 {
public:
    long long minimumPossibleSum(int n, int target) {
        int cnt = 0, i = 1;
        unordered_set<int> s;
        long long res = 0;
        while (cnt < n) {
            if (!s.count(target - i)) {
                res += i;
                s.emplace(i);
                ++cnt;
            }
            ++i;
        }
        return res;
    }
};

class Solution2 {
public:
    long long minimumPossibleSum(int n, int target) {
        int cnt = 0, i = 1;
        long long res = 0;
        while (cnt < n) {
            /* <= target / 2 的值任选，>= target 任选 */
            if (i <= (target >> 1) | i >= target) {
                res += i;
                ++cnt;
            }
            ++i;
        }
        return res;
    }
};

int main() {
    cout << Solution1().minimumPossibleSum(3, 3) << '\n';
    cout << Solution2().minimumPossibleSum(3, 3) << '\n';
    return 0;
}