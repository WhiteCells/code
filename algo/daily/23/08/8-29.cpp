#include "../../head_file.h"

/*
problme: 823. 带因子的二叉树
给出一个含有不重复整数元素的数组 arr ，每个整数 arr[i] 均大于 1。
用这些整数来构建二叉树，每个整数可以使用任意次数。其中：每个非叶结点的值应等于它的两个子结点的值的乘积。
满足条件的二叉树一共有多少个？答案可能很大，返回 对 109 + 7 取余 的结果。
输入: arr = [2, 4, 5, 10]
输出: 7
解释: 可以得到这些二叉树: [2], [4], [5], [10], [4, 2, 2], [10, 2, 5], [10, 5, 2].
提示：
    1 <= arr.length <= 1000
    2 <= arr[i] <= 109
    arr 中的所有值 互不相同
url: https://leetcode.cn/problems/binary-trees-with-factors/
*/

class Solution {
public:
    int numFactoredBinaryTrees(vector<int>& arr) {
        unordered_map<int, int> mp;
        sort(arr.begin(), arr.end());
        int mod = 1e9 + 7;
        for (const auto& root : arr) {
            mp[root] = 1;
            for (const auto& [r, x] : mp) {
                if (0 == root % r && mp.count(root / r)) { // r * (root / r) == root
                    mp[root] = ((long)mp[root] + mp[r] % mod * (long)mp[root / r]) % mod;
                }
            }
        }
        int cnt = 0;
        for (const auto& m : mp) {
            cnt = (cnt + m.second) % mod;
        }
        return cnt;
    }
};

int main() {
    vector<int> arr { 2, 4, 5, 10 };
    Solution s;
    cout << s.numFactoredBinaryTrees(arr) << '\n';
    return 0;
}