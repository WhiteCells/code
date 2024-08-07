#include "../../head_file.h"

/*
problme: 6450. k-avoiding 数组的最小总和
给你两个整数 n 和 k 。
对于一个由 不同 正整数组成的数组，如果其中不存在任何求和等于 k 的不同元素对，则称其为 k-avoiding 数组。
返回长度为 n 的 k-avoiding 数组的可能的最小总和。
url: https://leetcode.cn/problems/determine-the-minimum-sum-of-a-k-avoiding-array/
输入：n = 5, k = 4
输出：18
解释：设若 k-avoiding 数组为 [1,2,4,5,6] ，其元素总和为 18 。
可以证明不存在总和小于 18 的 k-avoiding 数组。
提示：
    1 <= n, k <= 50
@Author: Eorys
@Date: 2023-08-20 07:01:53
@Last Modified by: Eorys
@Last Modified time: 2023-08-20 07:01:53
@Description:
*/

/* 24ms 10.5 MB */
/* O(1) O(n) */
/*
map
 */
class Solution {
public:
    int minimumSum(int n, int k) {
        unordered_map<int, int> s;
        int cnt = 0, i = 1, res = 0;
        while (cnt < n) {
            if (s.find(k - i) == s.end()) {
                s[i] = 1;
                res += i;
                ++cnt;
            }
            ++i;
        }
        return res;
    }
};

/* 16ms 10.5 MB */
/* O(1) O(n) */
/*
set
 */
class Solution1 {
public:
    int minimumSum(int n, int k) {
        unordered_set<int> s;
        int cnt = 0, i = 1, res = 0;
        while (cnt < n) {
            if (s.find(k - i) == s.end()) {
                s.insert(i);
                res += i;
                ++cnt;
            }
            ++i;
        }
        return res;
    }
};

/* 4ms 5.76MB */
/* O(1) O(1) */
/*
划分成两段等差数列
m = min(k / 2, n)
m 为左边长度，必须要考虑 n，因为 n 可以小于 k
假设 n = 2，k = 6 此时 m 如果不考虑 n 则 m = k / 2 = 3，左边就错误的变成 3 结束
考虑 n 则 m = 2，求和的时候 (n - m) == 0
左边: [1, m]
右边: [k, k + (n - m + 1)]
等差数列求和
左边: (1 + m) * m / 2
右边: (2 * k + n - m - 1) * (n - m) / 2
 */
class Solution2 {
public:
    int minimumSum(int n, int k) {
        int m = min(k / 2, n), res = 0;
        return (1 + m) * m / 2 + (2 * k + n - m - 1) * (n - m) / 2;
    }
};


int main() {
    // int n = 1, k = 2;
    // Solution s;
    int n = 10, k = 6;
    Solution2 s;
    cout << s.minimumSum(n, k) << '\n';
    return 0;
}