#include "D:/distake/Coding/head_file.h"

/*
 * @Author: WhiteCells
 * @Date: 2023-05-16 19:21:18
 * @Last Modified by: WhiteCells
 * @Last Modified time: 2023-05-16 19:21:18
 * @Description: 445-分饼干
 * https://leetcode.cn/problems/assign-cookies/
*/


class Solution {
public:
    int findContentChildren(vector<int>& g, vector<int>& s) {
        sort(g.begin(), g.end());
        sort(s.begin(), s.end());
        int res = 0; // 最多能能满足的孩子的数量
        int sIndex = (int)s.size() - 1; // 饼干数组下标
        int gIndex = (int)g.size() - 1; // 孩子数组下标
        for (; gIndex >= 0; --gIndex) { // 遍历孩子数组
            // 当前最大饼干大于孩子胃口的时候将饼干喂给孩子，开始遍历下一个大饼干（下一次的最大）
            if (sIndex >= 0 && s[sIndex] >= g[gIndex]) {
                res++;    // 能满足的孩子数量自增
                sIndex--; // 开始遍历下一个大饼干饼干 
            }
        }
        return res;
    }
};

class Solution2 {
public:
    // 从最小胃口的开始喂
    int findContentChildren(vector<int>& g, vector<int>& s) {
        sort(g.begin(), g.end());
        sort(s.begin(), s.end());
        int res = 0;
        for (int i = 0, j = 0; i < (int)g.size(); ++i) {
            if (j < s.size() && s[j] >= g[i]) {
                ++j;
                ++res;
            }
        }
        return res;
    }
};


int main() {
    vector<int> g {1, 2};
    vector<int> s {1, 2, 3};
    Solution2 s1;
    cout << s1.findContentChildren(g, s);
    return 0;
}