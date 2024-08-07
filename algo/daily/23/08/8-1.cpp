#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
// https://leetcode.cn/problems/power-of-heroes/description/
/*
给你一个下标从 0 开始的整数数组 nums ，它表示英雄的能力值。如果我们选出一部分英雄，这组英雄的 力量 定义为：

    i0 ，i1 ，... ik 表示这组英雄在数组中的下标。那么这组英雄的力量为 max(nums[i0],nums[i1] ... nums[ik])2 * min(nums[i0],nums[i1] ... nums[ik]) 。

请你返回所有可能的 非空 英雄组的 力量 之和。由于答案可能非常大，请你将结果对 109 + 7 取余。

 

示例 1：

输入：nums = [2,1,4]
输出：141
解释：
第 1 组：[2] 的力量为 22 * 2 = 8 。
第 2 组：[1] 的力量为 12 * 1 = 1 。
第 3 组：[4] 的力量为 42 * 4 = 64 。
第 4 组：[2,1] 的力量为 22 * 1 = 4 。
第 5 组：[2,4] 的力量为 42 * 2 = 32 。
第 6 组：[1,4] 的力量为 42 * 1 = 16 。
第​ ​​​​​​7 组：[2,1,4] 的力量为 42​​​​​​​ * 1 = 16 。
所有英雄组的力量之和为 8 + 1 + 64 + 4 + 32 + 16 + 16 = 141 。
*/

class Solution {
public:
    int sumOfPower(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        long long mod = 1e9 + 7, ps = 0, res = 0;
        int n = nums.size();
        for (int i = 0; i < n; ++i) {
            res = (res + (ps + nums[i]) % mod * nums[i] % mod * nums[i]) % mod;
            ps = (2 * ps + nums[i]) % mod;
        }
        return (int)(res + mod) % mod;
    }
};


int main() {
    Solution s;
    auto nums = vector<int>{ 2, 1, 4 };
    cout << s.sumOfPower(nums);
    return 0;
}
