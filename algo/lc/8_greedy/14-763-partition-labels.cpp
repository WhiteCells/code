#include "D:/distake/Coding/head_file.h"

/*
 * @Author: WhiteCells
 * @Date: 2023-05-27 08:48:08
 * @Last Modified by: WhiteCells
 * @Last Modified time: 2023-05-27 08:48:08
 * @Description: 763. 划分字母区间
 * https://leetcode.cn/problems/partition-labels/
 * 输入：s = "ababcbacadefegdehijhklij"
 * 输出：[9,7,8]
 * 解释：
 * 划分结果为 "ababcbaca"、"defegde"、"hijhklij" 。
 * 每个字母最多出现在一个片段中。
 * 像 "ababcbacadefegde", "hijhklij" 这样的划分是错误的，因为划分的片段数较少。
*/

class Solution {
public:
    vector<int> partitionLabels(string s) {
        int lastPos[s.size()] = { 0 };
        for (int i = 0; i < s.size(); ++i) {
            lastPos[s[i] - 'a'] = i; // 当前字符在字符串中出现的最后位置
        }
        vector<int> res;
        int left = 0;
        int right = 0;
        for (int i = 0; i < s.size(); ++i) {
            right = max(right, lastPos[s[i] - 'a']); // 找最大右区间下标
            if (i == right) { // 当前遍历下标等于右区间下标，就是划分点
                res.push_back(right - left + 1); // 区间长度
                left = i + 1; // 更新左区间下标
            }
        }
        return res;
    }
};


int main() {
    Solution s;
    string str = "ababcbacadefegdehijhklij";
    vector<int> res = s.partitionLabels(str);
    for (auto& val : res) {
        cout << val << " ";
    }
    return 0;
}